#pragma once
// #include <btBulletDynamicsCommon.h>
#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../ACS/ASystem.hpp"
// #include "PhysicsComp.hpp"
#include "LinearMath/btVector3.h"
#include "../common/Symbol.hpp"

const btVector3 btVector3_ZERO = btVector3(0, 0, 0);

class Physics : public ASystem/*<PhysicsComp>*/ {
public:
  static Physics& get() { static Physics instance; return instance; } // singleton
  static shared_ptr<Physics>& getPtr() { static shared_ptr<Physics> ptr = shared_ptr<Physics>(&Physics::get(), [](Physics*) {}); return ptr; }

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

  Physics () { }

  class btBroadphaseInterface* broadphase = nullptr;
  class btDefaultCollisionConfiguration* collisionConfig = nullptr;
  class btCollisionDispatcher* dispatcher = nullptr;
  class btSequentialImpulseConstraintSolver* solver = nullptr;
  class btDiscreteDynamicsWorld* dynamicsWorld = nullptr;

  class DebugDrawer* debugDrawer = nullptr;
  bool drawDebug = false;

  bool init ();

  virtual void update (const vector<shared_ptr<AComp>>& comps, const float& dt) override;

  void deinit ();

  void debugDrawWorld();

  shared_ptr<class MeshComp> debugGetMesh();
};

