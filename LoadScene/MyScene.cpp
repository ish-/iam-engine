#include "MyScene.hpp"
#include "GUI.hpp"
#include "Actor.hpp"
#include "Physics/Physics.hpp"
#include "common/json.hpp"
#include "PlayerPhy.hpp"

#include "Physics/PhysicsComp.hpp"

// MyScene::MyScene () {}

void MyScene::init () {
  Scene::init();

  newActor<PlayerPhy>();

  // loadJson("resources/scenes/scene.json");
  loadJson("resources/scenes/box.json");


}

void MyScene::update(float dt) {
  auto box = getActorByName("lvl_box");
  auto testCubePhy = getActorByName("test-cube")->getComp<PhysicsComp>();
  auto boxPhy = box->getComp<PhysicsComp>();
  auto playerPhy = player->getComp<PhysicsComp>();

  if (auto contact = playerPhy->getContact()) {
    LOG("playerPhy contact",
      PhysicsComp::bodyToComp(contact.body1)->getOwner()->name,
      contact.impactSpeed, contact.penetrationDepth, contact.impactForce);
  }

  Scene::update(dt);
};

void MyScene::drawGui () {
  Scene::drawGui();

  // IMgui
}