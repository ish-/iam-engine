#pragma once
#include <functional>
#include "ACS/AComp.hpp"
#include "ILifecycle.hpp"
// TODO: fwd decl
#include "Actor.hpp"

class HealthComp : public AComp {
public:
  struct Conf {
    float health = 1.;
    float regen = 0.;
    float maxHealth = 1.;
    std::function<void(const float& damage, sp<Actor> actor)> takeDamageCallback = nullptr;
  };
  Conf conf;
  HealthComp (const Conf& conf): conf(conf), AComp() {};
  HealthComp ():  AComp() {};

  virtual void update (const float& dt) {
    conf.health += conf.regen * dt;
    if (conf.health <= 0) {
      getOwner()->release();
    } if (conf.health > conf.maxHealth) {
      conf.health = conf.maxHealth;
    }
  }

  virtual float takeDamage (const float& damage, sp<Actor> projectile) {
    conf.health -= damage;
    if (conf.takeDamageCallback) conf.takeDamageCallback(damage, projectile);
    return conf.health;
  }

  virtual float getHealth () {
    return conf.health;
  }
};
