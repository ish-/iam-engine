#pragma once
#include "Actor.hpp"
#include "Time.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Physics/PhysicsComp.hpp"
#include "HealthComp.hpp"

class Projectile : public Actor {
public:
  string getActorClassName() override { return "Projectile"; }
  struct Conf : public PhysicsComp::Params {
    glm::mat4 transform = glm::mat4(1.f);
    // glm::vec3 initialVelocity = glm::vec3(0, 0, -10);
    PhysicsComp::Params physics;
    float timeToLive = 5.f;
    bool releaseOnContact = true;
    float damage = .5f;
  };
  Conf conf;

  sp<PhysicsComp> phyComp;
  float createdAt = Time::get().eT;

  Projectile (const Conf& conf): conf(conf), Actor(conf.transform) {}

  virtual void init () override {
    Actor::init();
    auto scene = getScene();

    // setMatrix(conf.transform);
    // setName("Projectile-" + to_string(id));

    auto meshComp = scene->newComp<MeshComp>(shared_from_this(), MeshComp::Conf{
      .autoInstancing = false,
    });
    // meshComp->scale(.2);
    conf.physics.shapeSize = btVector3(.2f, .2f, 2.f);
    meshComp->scale(vec3(.033,.033,1.));

    // conf.physics.mask = PhysicsComp::PLAYER;
    phyComp = scene->newComp<PhysicsComp>(shared_from_this(), conf.physics);
    phyComp->rigidBody->setCcdMotionThreshold(0.03f);
    phyComp->rigidBody->setCcdSweptSphereRadius(0.1f);
  }

  virtual void update(const float& dt) override {
    bool toRelease = false;
    if (auto contact = phyComp->getContact()) {
      auto* otherPhyComp = PhysicsComp::fromBody(contact.body1);
      auto other = otherPhyComp->getOwner();

      string instigatorName = "__";
      auto ins = instigator.lock();
      bool selfFire = false;
      if (ins) {
        instigatorName = ins->name;
        selfFire = other->id == ins->id;
      }

      LOG("Projectile hit ", bool(contact), instigatorName, other->name);

        auto eHealthComp = other->getComp<HealthComp>();
        if (!selfFire && eHealthComp)
          eHealthComp->takeDamage(conf.damage, shared());

      if (conf.releaseOnContact)
        toRelease = true;
    }

    if (toRelease)
      return release();

    if (createdAt > 0.f && createdAt + conf.timeToLive < Time::get().eT)
      return release();

    Actor::update(dt);
  }
};
