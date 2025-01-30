#pragma once
// #include <btBulletDynamicsCommon.h>
#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../ACS/ASystem.hpp"
#include "PhysicsComponent.hpp"
#include "../common/Symbol.hpp"

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

  static glm::mat4 toGlmTMat4 (class btRigidBody* body);

  Physics ();

  class btBroadphaseInterface* broadphase = nullptr;
  class btDefaultCollisionConfiguration* collisionConfig = nullptr;
  class btCollisionDispatcher* dispatcher = nullptr;
  class btSequentialImpulseConstraintSolver* solver = nullptr;
  class btDiscreteDynamicsWorld* dynamicsWorld = nullptr;

  class DebugDrawer* debugDrawer = nullptr;
  bool drawDebug = false;

  bool init ();

  bool update (const float& dt);

  void deinit ();

  void debugDrawWorld();

  shared_ptr<class MeshComponent> debugGetMesh();
};

