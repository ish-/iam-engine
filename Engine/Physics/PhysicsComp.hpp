#pragma once
#include <memory>
#include "LinearMath/btVector3.h"
#include "../ACS/AComp.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include "../common/Symbol.hpp"
#include "../common/json.hpp"
#include "../Graphics/MeshComp.hpp"

// namespace nlohmann {
//     template <>
//     struct adl_serializer<btVector3> {
//         static void to_json(json& j, const btVector3& vec) {
//             j = json{{"x", vec.getX()}, {"y", vec.getY()}, {"z", vec.getZ()}};
//         }

//         static void from_json(const json& j, btVector3& vec) {
//             vec.setX(j.at("x").get<float>());
//             vec.setY(j.at("y").get<float>());
//             vec.setZ(j.at("z").get<float>());
//         }
//     };
// }

static void to_json(nlohmann::json& j, const btVector3& v) { j = nlohmann::json{v.getX(), v.getY(), v.getZ()};}
static void from_json(const nlohmann::json& j, btVector3& v) { j[0].get_to(v[0]); j[1].get_to(v[1]); j[2].get_to(v[2]); }

class Physics;
class btConvexInternalShape;
class btRigidBody;
class btCollisionShape;
class btDefaultMotionState;
class btBoxShape;

class PhysicsComp : public AComp {
public:
  struct Params {
    std::string shapeType = "BOX_SHAPE";
    btVector3 shapeSize = {.5, .5, .5};
    btVector3 pos {0,0,0};
    float mass = 0.;
    glm::vec2 damping = {0.,0.};
    btVector3 initialImpulse {0,0,0};
    btVector3 initialTorque {0,0,0};
    btVector3 intertia {0,0,0};
    // btVector3 initialImpulsePos {0,0,0};
    // float restitution = 0.5;
    // float friction = 0.5;

    JSON_DEFINE_OPTIONAL(Params, shapeType, pos, mass, damping, initialImpulse, initialTorque, intertia);
  };

  btCollisionShape* shape;

  virtual Symbol getASystemType () override {
      static Symbol symbol { "Physics" };
      return symbol;
  }

  Params params;

  PhysicsComp (const Params& params): params(params) {};
  PhysicsComp(): AComp() {}
  ~PhysicsComp ();

  // Physics& physics;

  // btConvexInternalShape* shape;
  btRigidBody* rigidBody;
  btDefaultMotionState* motionState;
  btVector3* inertia;

  // template<typename Shape = btBoxShape>
  bool init ();
  virtual void update(float dt) override;

  glm::mat4 getGlmTMat4 ();

  void applyForce (glm::vec3 force, glm::vec3 pos = {0,0,0});
  void applyTorque (glm::vec3 force);
};
