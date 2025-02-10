#include "GunComp.hpp"
#include "Time.hpp"

// GunComp::GunComp () {}

bool GunComp::isCooldown () {
  if (conf.cooldown > 0) {
    if (lastShootTime + conf.cooldown > Time::get().eT)
      return true;
  }
  return false;
}

void GunComp::shoot (vec3 targetPos) {
  if (isCooldown()) return;

  auto owner = getOwner();
  Transform transform = Transform(getOwner()->getAbsTransformMatrix());
  transform.translateLocal(conf.offset);

  // if (targetPos.x + targetPos.y + targetPos.z != 0.f) {
  if (glm::l1Norm(targetPos)) {
    quat rot = glm::quatLookAt(glm::normalize(targetPos - transform.getPosition()), vec3(0, 1, 0));;
    transform.setRotationQuat(rot);
  }

  auto forward = transform.getForward();
  auto projectile = owner->getScene()->newActor<Projectile>((Projectile::Conf){
    .transform = transform.getTransformMatrix(),
    .physics = (PhysicsComp::Params){
      .shapeType = "SPHERE_SHAPE",
      .mass = .05f,
      .initialImpulse = btVector3(forward.x, forward.y, forward.z) * 100.f,
    },
    .damage = .26f
  });
  projectile->instigator = owner;

  lastShootTime = Time::get().eT;
}
