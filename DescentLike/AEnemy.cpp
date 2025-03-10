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
    HealthComp::Conf{ .regen = .03 });

  meshComp = scene->newComp<MeshComp>(shared(),
    MeshComp::Conf{ .path = "resources/models/papership.obj" });

  phyComp = scene->newComp<PhysicsComp>(shared(), conf.physics);

  gunComp = scene->newComp<GunComp>(shared(), GunComp::Conf{ .offset = vec3(0,0,-1.5) });
}

#include <glm/gtx/matrix_interpolation.hpp>
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
      // // Proportional-Derivative
      // quat currentRot = glm::quat_cast(getAbsTransformMatrix());
      // quat targetRot = glm::rotation(getForward(), dirToTarget);
      // quat errorQuat = glm::inverse(currentRot) * targetRot;

      // vec3 errorAxis;
      // float errorAngle;
      // // glm::axisAngle(errorQuat, errorAxis, errorAngle);
      // errorAxis = glm::axis(errorQuat);
      // errorAngle = glm::angle(errorQuat);
      // vec3 error = errorAxis * errorAngle;

      // vec3 Kp = vec3(10.0f);  // Proportional gain
      // vec3 Kd = vec3(2.0f);

      // vec3 angularVelocity = Physics::toGlmVec3(phyComp->rigidBody->getAngularVelocity());
      // vec3 torque = Kp * error - Kd * angularVelocity;
      // // /////// Proportional-Derivative

      btTransform transform = phyComp->rigidBody->getWorldTransform();
      btQuaternion rotation = transform.getRotation();
      glm::quat glmRotation(rotation.w(), rotation.x(), rotation.y(), rotation.z());
      glm::vec3 forwardDirection = glmRotation * glm::vec3(0, 0, -1);

      float dot = glm::dot(forwardDirection, dirToTarget);
      float angle = acos(glm::clamp(dot, -1.0f, 1.0f)); // Clamp to avoid numerical errors
      glm::vec3 axis = glm::cross(forwardDirection, dirToTarget);
      axis = glm::normalize(axis);

      float kp = .5f; // gain
      btVector3 torque = btVector3(axis.x, axis.y, axis.z) * angle * kp;
      phyComp->rigidBody->applyTorque(torque);

      btVector3 angularVelocity = phyComp->rigidBody->getAngularVelocity();
      float damping = 0.08f;
      btVector3 dampingTorque = -angularVelocity * damping;
      phyComp->rigidBody->applyTorque(dampingTorque);

      if (angle < 0.01f) {
          phyComp->rigidBody->setAngularVelocity(btVector3(0, 0, 0));
      }

      // float rotationSpeed = .1;
      // vec3 torque = -rotationAxis * rotationAngle * rotationSpeed;
      // phyComp->applyTorque(torque);
    }


    float rotAxisLen2 = glm::length2(rotationAxis);
    if (rotAxisLen2 < pow(.2f, 2) && //
        glm::length2(toTarget) < pow(conf.shootDist, 2))
      gunComp->shoot(targetPos + rd::vec3in(-1, 1));

    vec3 moveDir = dirToTarget;
    if (glm::length2(toTarget) < pow(conf.hauntMinDist, 2))
      moveDir = -moveDir;
    phyComp->applyForce(moveDir * rotationDot);
  }

  Actor::update(dt);
}
