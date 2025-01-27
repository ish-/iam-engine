#pragma once
#include <btBulletDynamicsCommon.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../ACS/ASystem.hpp"
#include "PhysicsComponent.hpp"
#include "../../util/Symbol.hpp"
#include "DebugDraw.hpp"

const btVector3 btVector3_ZERO = btVector3(0, 0, 0);

class Physics : public ASystem<PhysicsComponent> {
public:
  static Physics& get() { static Physics instance; return instance; } // singleton
  virtual Symbol getASystemType () override {
      static Symbol symbol { "Physics" };
      return symbol;
  }

  static btVector3 toBtVec3(const glm::vec3& v) {
    return btVector3(v.x, v.y, v.z);
  }
  static glm::vec3 toGlmVec3(const btVector3& vec) {
    return glm::vec3(vec.getX(), vec.getY(), vec.getZ());
  }

  static glm::mat4 toGlmTMat4 (btRigidBody* body) {
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

  DebugDrawer* debugDrawer = nullptr;

  bool init ();

  bool update (const float& dt);

  void deinit ();
};

