#include "Physics.hpp"
// #include <btBulletDynamicsCommon.h>
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
// #include <btBulletCollisionCommon.h>
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "DebugDraw.hpp"
#include "../Graphics/MeshComp.hpp"

Physics::Physics () {}

glm::mat4 Physics::toGlmTMat4 (btRigidBody* body) {
  btTransform transform;
  body->getMotionState()->getWorldTransform(transform);
  btScalar matrix[16];
  transform.getOpenGLMatrix(matrix);
  return glm::make_mat4(matrix);
}

bool Physics::init () {
  // Initialize Bullet
  broadphase = new btDbvtBroadphase();
  collisionConfig = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfig);
  solver = new btSequentialImpulseConstraintSolver();
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
  // dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
  dynamicsWorld->setGravity(btVector3(0, 0, 0));

  debugDrawer = new DebugDrawer();
  dynamicsWorld->setDebugDrawer(debugDrawer);
  debugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawConstraints);

  return true;
}

bool Physics::update (const float& dt) {
  dynamicsWorld->stepSimulation(1.0f / 60.0f, 10);
  auto comps = getComps();
  for (auto& comp : comps) {
    if (auto aliveComp = comp.lock())
      aliveComp->update(dt);
  }
  return true;
}

void Physics::deinit () {
  delete dynamicsWorld;
  delete solver;
  delete dispatcher;
  delete collisionConfig;
  delete broadphase;
}

void Physics::debugDrawWorld() {
  if (drawDebug) {
    dynamicsWorld->debugDrawWorld();
  }
}

shared_ptr<MeshComp> Physics::debugGetMesh() {
  return debugDrawer->mesh;
}