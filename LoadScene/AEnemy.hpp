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
    auto player = scene->player;
    vec3 toPlayer = player->getPosition() - getPosition();
    vec3 dirToPlayer = normalize(toPlayer);
    vec3 radDir = dirToPlayer - getForward();
    // phyComp->applyTorque(radDir * 0.1f);
    phyComp->applyForce(dirToPlayer * 1.f);

    Actor::update(dt);
  }
};
