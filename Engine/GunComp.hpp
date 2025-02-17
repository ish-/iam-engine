#pragma once
#include "AComp.hpp"
#include "Projectile.hpp"

class GunComp : public AComp {
public:
  struct Conf {
    float cooldown = .5f;
    glm::vec3 offset = glm::vec3(0, 0, -1);
  };
  Conf conf;


  GunComp () {}
  GunComp (const Conf& conf): conf(conf) {}

  float lastShootTime = 0.f;

  void shoot (vec3 target = vec3(0));

  bool isCooldown ();
};
