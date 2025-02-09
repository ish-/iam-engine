#include "Physics.hpp"
// #include <btBulletDynamicsCommon.h>
#include "ACS/AComp.hpp"
#include "ACS/ASystem.hpp"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
// #include <btBulletCollisionCommon.h>
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "DebugDraw.hpp"
#include "../Graphics/MeshComp.hpp"
#include "./CollisionDispatcher.hpp"

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
  // dispatcher = new CollisionDispatcher(collisionConfig);
  solver = new btSequentialImpulseConstraintSolver();
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
  // dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
  dynamicsWorld->setGravity(btVector3(0, 0, 0));

  debugDrawer = new DebugDrawer();
  dynamicsWorld->setDebugDrawer(debugDrawer);
  debugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawConstraints);

  return true;
}

void Physics::update (const vector<shared_ptr<AComp>>& comps, const float& dt) {
  dynamicsWorld->stepSimulation(dt, 10);
  ASystem::update(comps, dt);
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