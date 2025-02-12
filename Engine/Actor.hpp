#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Physics/Physics.hpp"
#include "common/memory.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <typeindex>
// #include "common/id.hpp"
#include "Transform.hpp"
#include "Scene.hpp"
#include "ILifecycle.hpp"
#include "common/json.hpp"
#include "nlohmann/json_fwd.hpp"
// #include "ACS/AActor.hpp"
using namespace glm;
using namespace std;

class AComp;
class Scene;

class Actor : public ILifecycle, public Transform, public enable_shared_from_this<Actor> {
// protected:
public:
  static unsigned int getId () {
    static unsigned int id = 1;
    return id++;
  }

  virtual ~Actor();
  virtual string getActorClassName() { return "Actor"; }

  template<typename A = Actor>
  sp<A> shared() { return shared_from_this(); }

  Actor () {
    LOG("\n-- NEW ACTOR", id);
  };
  Actor (const mat4& transform) {
    setMatrix(transform);
  };

  vector<shared_ptr<Actor>> children;
  weak_ptr<Actor> parent;
  weak_ptr<Actor> instigator;
  void attach(const shared_ptr<Actor>& child);
  shared_ptr<Actor> getParent() const;

  // void attach(const Actor& child);

  mat4 getAbsTransformMatrix() const;

// AActor
  // TODO:

  // vector<shared_ptr<AComp>> comps;
  unordered_map<type_index, shared_ptr<AComp>> comps;

  unsigned int id = Actor::getId();
  string name = "";

  virtual void init() override;
  virtual void update(const float& dt) override;

  sp<Scene> getScene () { return scene.lock(); }
  wp<Scene> scene;

  template <typename T>
  shared_ptr<T> getComp() {
      type_index type = typeid(T);
      // LOG("getComp", type.name());
      // for (auto& [type, comp] : comps) {
      //     LOG("-- ", type.name());
      // }
      auto it = comps.find(type);
      if (it != comps.end()) {
          return dynamic_pointer_cast<T>(it->second);
      }
      return nullptr;
  }

  bool removeComp(shared_ptr<AComp> comp);

  // ~Actor();

  void setName (std::string name);

  void setTransformConf(const Transform::Conf& conf);

  // its cloning actor and all its components
  // virtual void clone() {
  //   auto actor = make_shared<Actor>();
  //   for (auto& [type, comp] : comps) {
  //     actor->comps[type] = comp->clone();
  //   }
  //   return actor;
  // };

  // void to_json(json& j) const {
  //   json jTransform = Transform::to_json();

  //   json jComps = json::object();
  //   for (const auto& [type, comp] : comps) {
  //       jComps[type.name()] = *comp;
  //   }

  //   j = json{
  //     {"id", id},
  //     {"pos", jTransform["pos"]},
  //     {"rot", jTransform["rot"]},
  //     {"scale", jTransform["scale"]},
  //     {"name", name},
  //     {"comps", jComps}
  //   };
  // };
  virtual void release () override { _released = true; }
  virtual bool isReleased () override { return _released; }

private:

  void _actorInit() {
    LOG("NEW Actor()", id, getActorClassName());
  }
  bool _released = false;
};
