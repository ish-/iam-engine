#pragma once
#include <btBulletDynamicsCommon.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Physics {
public:
  static Physics& get() { static Physics instance; return instance; } // singleton

  static btVector3 toBt(const glm::vec3& v) {
    return btVector3(v.x, v.y, v.z);
  }

  glm::mat4 btGetBodyGlTransform (btRigidBody* body) {
    btTransform transform;
    body->getMotionState()->getWorldTransform(transform);
    btScalar matrix[16];
    transform.getOpenGLMatrix(matrix);
    return glm::make_mat4(matrix);
  }

  Physics ();

  btBroadphaseInterface* broadphase = nullptr;
  btDefaultCollisionConfiguration* collisionConfig = nullptr;
  btCollisionDispatcher* dispatcher = nullptr;
  btSequentialImpulseConstraintSolver* solver = nullptr;
  btDiscreteDynamicsWorld* dynamicsWorld = nullptr;

  bool init () {
    // Initialize Bullet
    broadphase = new btDbvtBroadphase();
    collisionConfig = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfig);
    solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
    // dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
    dynamicsWorld->setGravity(btVector3(0, 0, 0));
    return true;
  }

  bool update () {
    dynamicsWorld->stepSimulation(1.0f / 60.0f, 10);
    return true;
  }

  void deinit () {
    // delete groundRigidBody->getMotionState();
    // delete groundRigidBody;
    // delete groundShape;

    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfig;
    delete broadphase;
  }
};

