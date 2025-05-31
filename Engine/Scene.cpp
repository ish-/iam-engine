#include "Scene.hpp"
#include <cstddef>
#include <memory>
#include "DebugTimer.hpp"
#include "common/json.hpp"
#include "Actor.hpp"
#include "ACube.hpp"
#include <imgui.h>
// #include "ASystem.hpp"
#include "Graphics/Renderer.hpp"
#include "Window.hpp"
#include "Physics/Physics.hpp"
#include "Inputs/Inputs.hpp"
#include "Physics/PhysicsComp.hpp"
#include "GUI.hpp"

#include "Transform.hpp"
#include "common/file.hpp"
#include "common/json-preprocess.hpp"

#include "Camera.hpp"
#include "Light.hpp"
#include "Time.hpp"
#include "Graphics/MeshComp.hpp"
// #include "Graphics/MeshModelComp.hpp"
using namespace std;
using namespace nlohmann;

void Scene::update (const float& dt) {
  auto inputs = Inputs::get();
  if (inputs.btnRel[SDLK_P] > 0.) pause = !pause;

  if (pause) {
    renderer->update(compsBySystem[renderer->getASystemType()], dt);
    return;
  }

  // update components per systems
  for (auto& [sysType, system] : systems) {
    DebugTimer timer("Scene::update " + sysType.name());
    system->update(compsBySystem[sysType], dt);
  }

  // update actors and clear
  size_t actorsNum = actors.size();
  for (size_t i = 0; i < actorsNum; i++) {
    auto& actor = actors[i];
    if (actor->isReleased()) {
      actors.erase(actors.begin() + i);
      actorsNum--;
      i--;
      continue;
    }
    actor->update(dt);
  }

  // clear compsBySystem once per second one per frame
  auto time = Time::get();
  size_t systemsNum = compsBySystem.size();
  size_t sysIdx = time.frame % 60;
  if (sysIdx < systemsNum) {
    auto it = compsBySystem.begin();
    std::advance(it, sysIdx);
    auto wComps = it->second;
    wComps.erase(
      std::remove_if(wComps.begin(), wComps.end(),
      [](const auto& wComp) { return wComp.expired(); }),
      wComps.end());
  }
}

void Scene::init() {
  physics = Physics::getPtr();
  physics->init();
  systems[physics->getASystemType()] = physics;

  renderer = Renderer::getPtr();
  renderer->setScene(shared_from_this());
  systems[renderer->getASystemType()] = renderer;

  compCtors["PhysicsComp"] = [this](const sp<Actor>& actor, const json& compJson) {
    return newComp<PhysicsComp>(actor, compJson.get<PhysicsComp::Params>());
  };

  actorCtors["Camera"] = [this](const json& actorJson) { return newActor<Camera>(actorJson.get<Camera::Conf>()); };
  actorCtors["Light"] = [this](const json& actorJson) {
    auto light = newActor<Light>(actorJson.get<Light::Conf>());
    lights.push_back(light);
    return light;
  };
  actorCtors["ACube"] = [this](const json& actor) { return newActor<ACube>(); };

  compCtors["MeshComp"] = [this](const sp<Actor>& actor, const json& compJson) {
    return newComp<MeshComp>(actor, compJson.get<MeshComp::Conf>());
  };
  // compCtors["MeshModelComp"] = [this](const sp<Actor>& actor, const json& compJson) {
  //   return newComp<MeshModelComp>(actor, compJson.get<MeshModelComp::Conf>());
  // };
}

bool sceneGui = false;
void Scene::drawGui () {
  using namespace ImGui;
  if (!GUI::get().conf.showDebug) return;
  if (!Begin("Scene", &sceneGui, ImGuiChildFlags_AutoResizeY | ImGuiWindowFlags_NoMove))
    return End();

  SetWindowSize(ImVec2(240, 0));
  SetWindowPos(ImVec2(Window::get().width - 240, 0));

  auto pos = player->getPosition();
  auto rot = player->getRotationEulAngles();
  Columns(4, "Camera");
    Text("Pos"); NextColumn();
    Text("%f", pos.x); NextColumn();
    Text("%f", pos.y); NextColumn();
    Text("%f", pos.z); NextColumn();
    Text("Rot"); NextColumn();
    Text("%f", rot.x); NextColumn();
    Text("%f", rot.y); NextColumn();
    Text("%f", rot.z); NextColumn();
  Columns(1);

  if (Inputs::get().btnRel[SDLK_K] > 0.)
    SetClipboardText(string("[" + to_string(pos.x) + ", " + to_string(pos.y) + ", " + to_string(pos.z) + "]"
      + ", [" + to_string(rot.x) + ", " + to_string(rot.y) + ", " + to_string(rot.z) + "]").c_str());

  // Text("Lights: %lu", lights.size());
  // Text("Actors: %lu", actors.size());
  string actorsHeader = "Actors: " + to_string(actors.size());
  if (CollapsingHeader("Actors:", ImGuiTreeNodeFlags_DefaultOpen)) {
    for (auto& actor : actors) {
      string actorHeader = actor->name + " (" + actor->getActorClassName() + ")";
      PushID(actor->id);
      if (TreeNode(actorHeader.c_str())) {
        for(auto& [type, comp] : actor->comps) {
          Text("Type: %s", type.name());
          ImGui::Separator();
        }

        TreePop();
      }
      PopID();

    }
  }


  ImGui::End();
}
void Scene::_addCompToActor (const sp<Actor>& actor, const type_index& typeId, const sp<AComp>& comp) {
  // LOG("Scene::addComp", actor->name, actor->id, typeId.name());
  actor->comps[typeId] = comp;
  comp->setOwner(actor);
}

void Scene::loadJson (string path) {
  using namespace nlohmann;
  LOG("<<< Loading scene", path);
  json data = json::parse(JsonPreprocess::removeComments(loadFile(path)));

  if (data.contains("actors") && data["actors"].is_array()) {
    for (const auto& actor : data["actors"]) {
      if (actor.contains("skip") && actor["skip"])
        continue;

      string type = "";
      bool typeExists = false;

      if (actor.contains("type")) {
        type = actor["type"];
        std::cout << "\nActor Type: " << type << "\n";
        typeExists = actorCtors.contains(type);
      }

      auto sceneActor = typeExists ? actorCtors[type](actor) : newActor<Actor>();

      auto transformConf = actor.get<Transform::Conf>();
      sceneActor->setTransformConf(transformConf);

      if (actor.contains("name")) {
        std::string actorName = actor["name"];
        std::cout << "Name: " << actorName << "\n";
        sceneActor->name = actorName;
        actorsByName[actorName] = sceneActor;
      }

      if (actor.contains("comps") && actor["comps"].is_array()) {
        for (const auto& comp : actor["comps"]) {
          std::string compType = comp["type"];
          std::cout << "Comp Type: " << compType << "\n";

          if (compCtors.contains(compType))
            compCtors[compType](sceneActor, comp);
          else
            LOG("Unknown comp type!!!", compType);
        }
      }

      // if (actor.contains("attach") && actor["attach"].is_array()) {
      //   for (const auto& childName : actor["attach"])
      //     sceneActor->attach(getActorByName(childName));
      // }
    }
  }
  LOG("<<< Scene loaded");
}