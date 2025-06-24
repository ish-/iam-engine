#include "DLScene2.hpp"
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
#include "glm/ext/vector_float3.hpp"

// DLScene2::DLScene2 () {}

void DLScene2::init () {
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

  // auto boxLvl = newActor();
  // auto boxMesh = newComp<MeshComp>(boxLvl, MeshComp::Conf{
  //   .path = "resources/scenes/lvl_box2.fbx",
  // });
  // boxMesh->conf.tint = vec3(0.4, 0.4, 0.5);
  // // boxMesh->material->uniforms.set("sAlbedo", AssetStore::get().loadTexture("scenes/likeabluenoise.jpg", 4));
  // // boxMesh->material->uniforms.set("uUvScale", 3.f);
  // newComp<PhysicsComp>(boxLvl, PhysicsComp::Params{
  //   .shapeType = "TRIANGULATE_SHAPE",
  //   .mass = 0,
  //   .friction = 1.f,
  // });

  asteroidMat = AssetStore::get().createMaterial<PhongMaterial>("asteroid", UniformsMap{
    {"sAlbedo", AssetStore::get().loadTexture("scenes/likeabluenoise.jpg", 4)},
    {"uShininess", 1.f},
  });
  for (size_t i = 0; i < 400; i++) {
    auto asteroid = newActor<AAsteroid>();
    asteroid->setTransformConf((Transform::Conf){
      rd::vec3in(-20, 20),
      rd::vec3in(-180,180)
    });
    asteroid->getComp<PhysicsComp>()->rigidBody->applyCentralForce(btVector3(rd::in(-10, 10),rd::in(-10, 10),rd::in(-10, -5)));
    asteroid->getComp<PhysicsComp>()->rigidBody->applyTorque(btVector3(rd::in(-30, 30),rd::in(-30, 30),rd::in(-30, -30)));
    asteroid->getComp<MeshComp>()->material = asteroidMat;
  }
  for (size_t i = 0; i < 10; i++) {
    auto enemy = newActor<AEnemy>(AEnemy::Conf{
      .hauntDist = 50.f,
      .hauntMinDist = 1.f,
      .shootDist = 20.f,
    });
    enemy->setTransformConf(Transform::Conf{
      rd::vec3in(-15, 15),
      rd::vec3in(-180,180)
    });
  }
}

void DLScene2::update (const float& dt) {
  dynamic_pointer_cast<PlayerPhy>(player)
    ->light->conf.intensity = sin(Time::get().eT * 5) * .1f + 1;

  // asteroidMat->uniforms.set("uUvScale", float(1.f + sin(Time::get().eT * 2) * .5f));

  Scene::update(dt);
};
