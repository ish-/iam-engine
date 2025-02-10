#pragma once
#include "Actor.hpp"
#include "Time.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Physics/PhysicsComp.hpp"

class Projectile : public Actor {
public:
string getActorClassName() override { return "Projectile"; }
  struct Conf : public PhysicsComp::Params {
    glm::mat4 transform = glm::mat4(1.);
    // glm::vec3 initialVelocity = glm::vec3(0, 0, -10);
    PhysicsComp::Params physics;
    float timeToLive = 5.f;
    bool releaseOnContact = true;
  };
  Conf conf;

  sp<PhysicsComp> phyComp;
  float createdAt = Time::get().eT;

  Projectile (const Conf& conf): conf(conf), Actor(conf.transform) {}

  virtual void init () override {
    Actor::init();
    auto scene = getScene();

    setMatrix(conf.transform);
    // setName("Projectile-" + to_string(id));

    auto meshComp = scene->newComp<MeshComp>(shared_from_this());
    meshComp->scale(.2);

    phyComp = scene->newComp<PhysicsComp>(shared_from_this(), conf.physics);
    phyComp->rigidBody->setCcdMotionThreshold(0.1f);
    phyComp->rigidBody->setCcdSweptSphereRadius(0.2f);
  }

  virtual void update(const float& dt) override {
    if (auto contact = phyComp->getContact()) {
      // auto* other = PhysicsComp::fromBody(contact.body1);
      // LOG("Projectile hit ", other->getOwner()->name);
      if (conf.releaseOnContact)
        return release();
    }

    if (createdAt > 0.f && createdAt + conf.timeToLive < Time::get().eT)
      return release();

    Actor::update(dt);
  }
};
