#include "Physics.hpp"

Physics::Physics () {}

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
  auto comps = getComponents();
  for (auto& comp : comps) {
    comp->update(dt);
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