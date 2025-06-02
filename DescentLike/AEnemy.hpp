#pragma once
#include "Engine/Actor.hpp"
#include "Engine/Physics/PhysicsComp.hpp"
#include "Transform.hpp"
#include "common/json.hpp"

class AEnemy : public Actor {
public:
  std::string getActorClassName() override { return "Enemy"; }
  struct Conf {
    glm::mat4 transform = I_MAT;
    float hauntDist = 20.f;
    float hauntMinDist = 4.f;
    float shootDist = 13.f;
    PhysicsComp::Params physics {
      .shapeType = "SPHERE_SHAPE",
      .shapeSize = btVector3(1, 1, 1),
      .mass = 1.,
      .group = PhysicsComp::ENEMY,
    };

    JSON_DEFINE_OPTIONAL(Conf, hauntDist, hauntMinDist, shootDist, physics);
  };
  Conf conf;
  sp<PhysicsComp> phyComp;
  sp<class MeshComp> meshComp;
  sp<class GunComp> gunComp;

  float dying = 0;

  AEnemy (const Conf& conf): conf(conf), Actor(conf.transform) {};

  virtual void init () override;
  virtual void update(const float& dt) override;
};
