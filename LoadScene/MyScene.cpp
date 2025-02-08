#include "MyScene.hpp"
#include "GUI.hpp"
#include "Physics/Physics.hpp"
#include "Physics/PhysicsComp.hpp"
#include "Actor.hpp"
#include "common/json.hpp"

// MyScene::MyScene () {}

void MyScene::init () {
  Scene::init();
  auto actor = newActor<Actor>();
  // auto comp = newComp<PhyComp>(actor);
  loadJson("resources/scenes/scene.json");
  auto a = getActorByName("1st-model");
  auto meshComp = a->getComp<MeshComp>();
  a->setPosition(vec3(-1,0,0));
  if (meshComp)
    LOG("tint", meshComp->tint.x, meshComp->tint.y, meshComp->tint.z);

  auto& physics = Physics::getPtr();
  systems[physics->getASystemType()] = physics;

  compCtors["PhysicsComp"] = [this](const sp<Actor>& actor, const json& comp) {
    return addComp<PhysicsComp>(actor, std::make_shared<PhysicsComp>(comp.get<PhysicsComp>()));
  };
}

void MyScene::drawGui () {
  Scene::drawGui();

  // IMgui
}