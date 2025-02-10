#pragma once
#include "Engine/Actor.hpp"
#include "Engine/Physics/PhysicsComp.hpp"

class AEnemy : public Actor {
public:
  std::string getActorClassName() override { return "Enemy"; }
  struct Conf {
    glm::mat4 transform = glm::mat4(1.);
    float hauntDist = 40.f;
    float hauntMinDist = 4.f;
    float shootDist = 20.f;
    PhysicsComp::Params physics;
  };
  Conf conf;
  sp<PhysicsComp> phyComp;
  sp<class MeshComp> meshComp;
  sp<class GunComp> gunComp;

  AEnemy (const Conf& conf): conf(conf), Actor(conf.transform) {};

  virtual void init () override;
  virtual void update(const float& dt) override;
};
