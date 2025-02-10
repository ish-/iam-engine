#include "Scene.hpp"
#include <cstddef>
#include <memory>
#include "common/json.hpp"
#include "Actor.hpp"
#include "ACube.hpp"
// #include "ACS/ASystem.hpp"
#include "Graphics/Renderer.hpp"
#include "Physics/Physics.hpp"
#include "Physics/PhysicsComp.hpp"

#include "Transform.hpp"
#include "common/file.hpp"
#include "common/json-preprocess.hpp"

#include "Camera.hpp"
#include "Light.hpp"
#include "Time.hpp"
#include "Graphics/MeshComp.hpp"
#include "Graphics/MeshModelComp.hpp"
using namespace std;
using namespace nlohmann;

void Scene::update (const float& dt) {
  // update components per systems
  for (auto& [sysType, system] : systems)
    system->update(compsBySystem[sysType], dt);

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
  compCtors["MeshModelComp"] = [this](const sp<Actor>& actor, const json& compJson) {
    return newComp<MeshModelComp>(actor, compJson.get<MeshModelComp::Conf>());
  };
}

void Scene::drawGui () {

}
void Scene::_addCompToActor (const sp<Actor>& actor, const type_index& typeId, const sp<AComp>& comp) {
  LOG("Scene::addComp", actor->name, actor->id, typeId.name());
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