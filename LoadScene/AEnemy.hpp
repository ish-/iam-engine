#pragma once
#include "Engine/Actor.hpp"
#include "Engine/Transform.hpp"
#include "Engine/Graphics/MeshComp.hpp"
#include "Engine/Physics/PhysicsComp.hpp"
#include "Engine/HealthComp.hpp"

class AEnemy : public Actor {
public:
  std::string getActorClassName() override { return "Enemy"; }
  struct Conf {
    glm::mat4 transform = glm::mat4(1.);
    PhysicsComp::Params physics;
  };
  Conf conf;
  sp<PhysicsComp> phyComp;
  sp<MeshComp> meshComp;

  AEnemy (const Conf& conf): conf(conf), Actor(conf.transform) {};

  virtual void init () override {
    Actor::init();
    setName("Enemy-" + to_string(id));
    auto scene = getScene();

    scene->newComp<HealthComp>(shared_from_this(),
      (HealthComp::Conf){ .regen = .03 });

    meshComp = scene->newComp<MeshComp>(shared_from_this());

    phyComp = scene->newComp<PhysicsComp>(shared_from_this(), conf.physics);
  }

  virtual void update(const float& dt) override {
    float health = getComp<HealthComp>()->getHealth();
    meshComp->conf.tint = glm::min(meshComp->conf.tint + vec3(.01), vec3(1, health, health));

    auto scene = getScene();
    auto target = scene->player;
    vec3 toTarget = target->getPosition() - getPosition();
    vec3 dirToTarget = normalize(toTarget);
    vec3 forward = getForward();
    vec3 rotationAxis = glm::cross(dirToTarget, forward);
    float rotationDot = glm::dot(forward, dirToTarget);
    float rotationAngle = glm::acos(rotationDot);

    if (glm::length(rotationAxis) > 0) {
      float rotationSpeed = .1;
      vec3 torque = rotationAxis * rotationAngle * rotationSpeed;
      phyComp->applyTorque(torque);
    }

    phyComp->applyForce(forward * rotationDot);

    Actor::update(dt);
  }
};
