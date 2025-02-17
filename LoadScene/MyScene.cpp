#include "MyScene.hpp"
#include "Engine/GUI.hpp"
#include "Engine/Actor.hpp"
#include "Engine/PlayerPhy.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

// #include "Engine/Physics/PhysicsComp.hpp"
#include "AEnemy.hpp"
#include "ACube.hpp"
#include "Engine/common/random.hpp"
#include "Engine/common/screenToWorld.hpp"
#include "Transform.hpp"

// MyScene::MyScene () {}

void MyScene::init () {
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


  // loadJson("resources/scenes/scene.json");
  // loadJson("resources/scenes/box.json");
  loadJson("resources/scenes/lvl_station.json");


  for (size_t i = 0; i < 100; i++) {
    auto cube = newActor<ACube>();
    cube->setTransformConf((Transform::Conf){vec3(0,0,-5) + vec3(rd::in(-15,15), rd::in(-5,5), rd::in(0, 30)), rd::vec3in(-15,15), rd::vec3in(-180,180)});
  }
}

void MyScene::update (const float& dt) {
  Scene::update(dt);
};

// #include "Engine/Inputs/Inputs.hpp"
// #include "Engine/Graphics/Window.hpp"
// #include "Engine/Physics/Ray.hpp"
// void MyScene::castMouseRay () {
//   auto inputs = Inputs::get();
//   auto w = Window::get();
//   vec3 worldMouseDir = screenToWorldDir(inputs.mouse.x, inputs.mouse.y, w.width, w.height,
//     camera->getAbsTransformMatrix(), camera->projection);
//   // Ray ray;
//   Ray ray (+Transform(player->getAbsTransformMatrix()).getPosition());
//   if (PhysicsComp* phyComp = ray.castInDir(+worldMouseDir, 100).getHitPhysicsComp())
//     phyComp->getOwner()->getComp<MeshComp>()->conf.tint = vec3(0, 0, 1);
// }

void MyScene::drawGui () {
  Scene::drawGui();
  // IMgui
}