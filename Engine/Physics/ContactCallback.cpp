#include "ContactCallback.hpp"

btScalar ContactCallback::addSingleResult(
  btManifoldPoint& cp,
  const btCollisionObjectWrapper* colObj0,
  int partId0,
  int index0,
  const btCollisionObjectWrapper* colObj1,
  int partId1,
  int index1
) {
  bCollided = true;
  // btVector3 collisionNormal = cp.m_normalWorldOnB;
  btVector3 velocity0 = btVector3(0, 0, 0);
  btVector3 velocity1 = btVector3(0, 0, 0);

  const btRigidBody* body0 = btRigidBody::upcast(colObj0->getCollisionObject());
  const btRigidBody* body1 = btRigidBody::upcast(colObj1->getCollisionObject());

  // int mask0 = colObj0->getCollisionObject()->getBroadphaseHandle()->m_collisionFilterMask;
  // int group0 = colObj0->getCollisionObject()->getBroadphaseHandle()->m_collisionFilterGroup;

  if (body0) velocity0 = body0->getLinearVelocity();
  if (body1) velocity1 = body1->getLinearVelocity();

  btVector3 relativeVelocity = velocity0 - velocity1;
  float impactSpeed = relativeVelocity.length();
  float penetrationDepth = cp.m_distance1;
  float impactForce = body0->getMass() * body1->getMass() * impactSpeed;

  result.normal = cp.m_normalWorldOnB;
  result.velocity0 = velocity0;
  result.velocity1 = velocity1;
  result.impactSpeed = impactSpeed;
  result.penetrationDepth = penetrationDepth;
  result.impactForce = impactForce;
  result.body0 = body0;
  result.body1 = body1;

  // std::cout << "Collision detected!" << std::endl;
  // std::cout << "Impact speed: " << impactSpeed << std::endl;
  // std::cout << "Penetration depth: " << penetrationDepth << std::endl;
  // std::cout << "Impact force: " << impactForce << std::endl;

  return cp.m_appliedImpulse;
}