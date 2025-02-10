#pragma once
#include "ACS/AComp.hpp"
#include "Actor.hpp"

class HealthComp : public AComp {
public:
  struct Conf {
    float health = 1.;
    float regen = 0.;
  };
  Conf conf;
  HealthComp (const Conf& conf): conf(conf), AComp() {};
  HealthComp ():  AComp() {};

  virtual void update (const float& dt) {
    conf.health += conf.regen * dt;
    if (conf.health <= 0) {
      getOwner()->release();
    }
  }

  virtual float takeDamage (const float& damage) {
    return conf.health -= damage;
  }

  virtual float getHealth () {
    return conf.health;
  }
};
