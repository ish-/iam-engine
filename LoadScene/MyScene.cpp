#include "MyScene.hpp"
#include "Engine/GUI.hpp"
#include "Engine/Actor.hpp"
#include "Engine/PlayerPhy.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Physics/PhysicsComp.hpp"
#include "AEnemy.hpp"
#include "Engine/common/random.hpp"

// MyScene::MyScene () {}

void MyScene::init () {
  Scene::init();

  newActor<PlayerPhy>();

  for (size_t i = 0; i < 10; i++) {
    newActor<AEnemy>((AEnemy::Conf){
      .transform = Transform(vec3(rd::in(-5, 5), rd::in(-5, 5), rd::in(-5, 5))).getTransformMatrix(),
      .physics = (PhysicsComp::Params){
        .mass = 1.,
        .damping = glm::vec2(.3, .3),
        .group = PhysicsComp::ENEMY,
      }
    });
  }

  // loadJson("resources/scenes/scene.json");
  loadJson("resources/scenes/box.json");


}

void MyScene::update(float dt) {
  auto box = getActorByName("lvl_box");
  // auto testCubePhy = getActorByName("test-cube")->getComp<PhysicsComp>();
  auto boxPhy = box->getComp<PhysicsComp>();
  auto playerPhy = player->getComp<PhysicsComp>();

  if (auto contact = playerPhy->getContact()) {
    LOG("playerPhy contact",
      PhysicsComp::fromBody(contact.body1)->getOwner()->name,
      contact.impactSpeed, contact.penetrationDepth, contact.impactForce);
  }

  Scene::update(dt);
};

void MyScene::drawGui () {
  Scene::drawGui();

  // IMgui
}