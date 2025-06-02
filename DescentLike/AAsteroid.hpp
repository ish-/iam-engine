#pragma once
#include "Actor.hpp"
#include "Physics/PhysicsComp.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/PhongMaterial.hpp"
#include <memory>

// class PhysicsComp;

class AAsteroid : public Actor {
public:
  string getActorClassName() override { return "AAsteroid"; }

  void init() override {
    Actor::init();
    auto ctr = getScene();

    auto meshComp = ctr->newComp<MeshComp>(shared_from_this(), MeshComp::Conf{
      .path = "resources/models/asteroid2.fbx"
    });
    meshComp->scale(.7f);
    auto mat = meshComp->material = make_shared<PhongMaterial>();
    mat->albedoTex = AssetStore::get().loadTexture("scenes/likeabluenoise.jpg", 4);
    mat->conf.uvScale = 0.5f;
    if (auto mat = dynamic_pointer_cast<PhongMaterial>(meshComp->material)) {
      mat->conf.shininess = 200.f;
    }
    // meshComp->conf.tint = glm::vec3(.3f, 0.1f, 0.1f);

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
