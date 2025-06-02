#include "DLScene1.hpp"
#include "Engine/Engine.hpp"
#include "Engine/GUI.hpp"
#include "Engine/Actor.hpp"
#include "Engine/PlayerPhy.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <memory>

// #include "Engine/Physics/PhysicsComp.hpp"
#include "AEnemy.hpp"
#include "ACube.hpp"
#include "Physics/PhysicsComp.hpp"
#include "Time.hpp"
#include "AAsteroid.hpp"
#include "Engine/common/random.hpp"
#include "Engine/common/screenToWorld.hpp"
#include "Graphics/MeshComp.hpp"
#include "Graphics/Material.hpp"
#include "Transform.hpp"
#include "Light.hpp"
#include "Graphics/Geo.hpp"
#include "Graphics/Frustrum.hpp"

// DLScene1::DLScene1 () {}

void DLScene1::init () {
  Scene::init();

  // actorCtors["AEnemy"] = [this](const json& actorJson) {
  //   return newActor<AEnemy>(actorJson.get<AEnemy::Conf>());
  // };
  actorCtors["AEnemy"] = [this](const json& actorJson) { return newActor<AEnemy>(actorJson.get<AEnemy::Conf>()); };
  // actorCtors["PlayerPhy"] = [this](const json& actorJson) { return newActor<PlayerPhy>(actorJson.get<PlayerPhy::Conf>()); };
  player = newActor<PlayerPhy>();
  player->setTransformConf(Transform::Conf{
    .pos = vec3(0, 0, -5),
    .rot = vec3(0, 180, 0),
  });

  loadJson("resources/scenes/lvl_station.json");
  auto stationMesh = getActorByName("lvl_station")->getComp<MeshComp>();
  stationMesh->material->conf.worldAlignedTexture = true;
  stationMesh->material->conf.uvScale = .5f;
  stationMesh->material->albedoTex = AssetStore::get().loadTexture("scenes/likeabluenoise.jpg", 4);
  // stationMesh->conf.tint = glm::vec3(.7f, 0.7f, 1.f);

  // Engine::get().pause = true;

  for (size_t i = 0; i < 100; i++) {
    auto asteroid = newActor<AAsteroid>();
    asteroid->setTransformConf((Transform::Conf){
      vec3(0,0,-5) + vec3(
        rd::in(-15,15),
        rd::in(-5,5),
        rd::in(0, 30)
      ),
      rd::vec3in(-180,180)
    });
    asteroid->getComp<PhysicsComp>()->rigidBody->applyCentralForce(btVector3(rd::in(-10, 10),rd::in(-10, 10),rd::in(-10, -5)));
  }
}

void DLScene1::update (const float& dt) {
  dynamic_pointer_cast<PlayerPhy>(player)
    ->light->conf.intensity = sin(Time::get().eT * 5) * .1f + 1;

  Scene::update(dt);
};

// #include "Engine/Inputs/Inputs.hpp"
// #include "Engine/Window.hpp"
// #include "Engine/Physics/Ray.hpp"
// void DLScene1::castMouseRay () {
//   auto inputs = Inputs::get();
//   auto w = Window::get();
//   vec3 worldMouseDir = screenToWorldDir(inputs.mouse.x, inputs.mouse.y, w.width, w.height,
//     camera->getAbsTransformMatrix(), camera->projection);
//   // Ray ray;
//   Ray ray (+Transform(player->getAbsTransformMatrix()).getPosition());
//   if (PhysicsComp* phyComp = ray.castInDir(+worldMouseDir, 100).getHitPhysicsComp())
//     phyComp->getOwner()->getComp<MeshComp>()->conf.tint = vec3(0, 0, 1);
// }

void DLScene1::drawGui () {
  Scene::drawGui();
  // IMgui
}