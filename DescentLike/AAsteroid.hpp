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
    meshComp->scale(.7f);

    PhysicsComp::Params createParams {
      .shapeType = "SPHERE_SHAPE",
      .shapeSize = btVector3(.5, .5, .5),
      .mass = 1.,
      .friction = 1.f,
      .disableCulled = true,
    };
    ctr->newComp<PhysicsComp>(shared_from_this(), createParams);
  };
};
