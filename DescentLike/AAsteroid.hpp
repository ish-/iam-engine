#pragma once
#include "Actor.hpp"
#include "Graphics/AssetStore.hpp"
#include "Physics/PhysicsComp.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/PhongMaterial.hpp"
#include "Time.hpp"
#include <memory>

// class PhysicsComp;

class AAsteroid : public Actor {
public:
  string getActorClassName() override { return "AAsteroid"; }

  static sp<PhongMaterial> mat;

  void init() override {
    Actor::init();
    auto ctr = getScene();

    auto meshComp = ctr->newComp<MeshComp>(shared_from_this(), MeshComp::Conf{
      .path = "resources/models/asteroid2.fbx"
    });
    meshComp->scale(.7f * 4);

    PhysicsComp::Params createParams {
      .shapeType = "SPHERE_SHAPE",
      .shapeSize = btVector3(.8, .8, .8) * 4,
      .mass = 1.,
      .friction = 1.f,
      .disableCulled = true,
    };
    ctr->newComp<PhysicsComp>(shared_from_this(), createParams);
  };

  void update(const float& dt) override {
    auto phyComp = getComp<PhysicsComp>();
    auto pos = getPosition();
    phyComp->applyForce(vec3(0.) - pos * 0.01f);

    Actor::update(dt);
  }
};