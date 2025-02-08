#include "Scene.hpp"
#include <cstddef>
#include <memory>
#include "common/json.hpp"
#include "Actor.hpp"
#include "ACube.hpp"
// #include "ACS/ASystem.hpp"
#include "Graphics/Renderer.hpp"
#include "Transform.hpp"
#include "common/file.hpp"

#include "Camera.hpp"
#include "Light.hpp"
#include "Graphics/MeshComp.hpp"
using namespace std;
using namespace nlohmann;

void Scene::update(float dt) {
  for (auto& actor : actors) {
    actor->update(dt);
  }

  for (auto& [sysType, wpSystem] : systems) {
    if (auto system = wpSystem.lock())
      system->update(compsBySystem[sysType], dt);
  }
}

void Scene::init() {
  auto& renderer = Renderer::getPtr();
  renderer->setScene(shared_from_this());
  systems[renderer->getASystemType()] = renderer;

  actorCtors["Camera"] = [this](const json& actor) { return (camera = addActor(actor.get<Camera>())); };
  actorCtors["Light"] = [this](const json& actor) {
    auto light = addActor(actor.get<Light>());
    lights.push_back(light);
    return light;
  };
  actorCtors["ACube"] = [this](const json& actor) { return newActor<ACube>(); };

  compCtors["MeshComp"] = [this](const sp<Actor>& actor, const json& comp) {
    return addComp<MeshComp>(actor, std::make_shared<MeshComp>(comp.get<MeshComp>()));
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
  json data = json::parse(loadFile(path));

  if (data.contains("actors") && data["actors"].is_array()) {
    for (const auto& actor : data["actors"]) {
      sp<Actor> sceneActor = nullptr;

        if (actor.contains("type")) {
          std::string type = actor["type"];
          std::cout << "\nActor Type: " << type << "\n";

          if (actorCtors.contains(type))
            sceneActor = actorCtors[type](actor);
        }
        if (!sceneActor)
          sceneActor = newActor<Actor>();

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
          }
        }

        // if (actor.contains("attach") && actor["attach"].is_array()) {
        //   for (const auto& childName : actor["attach"])
        //     sceneActor->attach(getActorByName(childName));
        // }
    }
  }
}