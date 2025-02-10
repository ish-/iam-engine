#include "AEnemy.hpp"
#include "Engine/Projectile.hpp"
#include "Engine/Transform.hpp"
#include "Engine/Graphics/MeshComp.hpp"
#include "Engine/Physics/PhysicsComp.hpp"
#include "Engine/HealthComp.hpp"
#include "Engine/GunComp.hpp"

// AEnemy::AEnemy () {}

void AEnemy::init () {
  Actor::init();
  setName("Enemy-" + to_string(id));
  auto scene = getScene();

  scene->newComp<HealthComp>(shared(),
    (HealthComp::Conf){ .regen = .03 });

  meshComp = scene->newComp<MeshComp>(shared(),
    MeshComp::Conf{ .path = "resources/models/papership.obj" });

  phyComp = scene->newComp<PhysicsComp>(shared(), conf.physics);

  gunComp = scene->newComp<GunComp>(shared(), GunComp::Conf{ .offset = vec3(0,0,-1.5) });
}

void AEnemy::update(const float& dt) {
  float health = getComp<HealthComp>()->getHealth();
  meshComp->conf.tint = glm::min(meshComp->conf.tint + vec3(.01), vec3(1, health, health));

  auto scene = getScene();
  auto target = scene->player;
  vec3 targetPos = target->getPosition();
  vec3 toTarget = targetPos - getPosition();

  bool toHaunt = glm::length2(toTarget) < pow(conf.hauntDist, 2);

  if (toHaunt) {
    vec3 dirToTarget = normalize(toTarget);
    vec3 forward = getForward();
    vec3 rotationAxis = glm::cross(dirToTarget, forward);
    float rotationDot = glm::dot(forward, dirToTarget);
    float rotationAngle = glm::acos(rotationDot);

    if (glm::length(rotationAxis) > 0) {
      float rotationSpeed = .1;
      vec3 torque = -rotationAxis * rotationAngle * rotationSpeed;
      phyComp->applyTorque(torque);
    }

    if (glm::length2(rotationAxis) < pow(.2f, 2) && //
        glm::length2(toTarget) < pow(conf.shootDist, 2))
      gunComp->shoot(targetPos + rd::vec3in(-1, 1));

    if (glm::length2(toTarget) < pow(conf.hauntMinDist, 2))
      forward = -forward;
    phyComp->applyForce(forward * rotationDot);
  }

  Actor::update(dt);
}
