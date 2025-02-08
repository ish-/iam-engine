#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "common/memory.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include "common/id.hpp"
#include "Transform.hpp"
#include "Scene.hpp"
#include "ILifecycle.hpp"
// #include "ACS/AActor.hpp"
using namespace glm;
using namespace std;

class AComp;
class Scene;

class Actor : public ILifecycle, public Transform, public enable_shared_from_this<Actor> {
// protected:
public:
  Actor () { LOG("new Actor()"); };

  vector<shared_ptr<Actor>> children;
  weak_ptr<Actor> parent;
  void attach(const shared_ptr<Actor>& child);
  shared_ptr<Actor> getParent() const;

  // void attach(const Actor& child);

  mat4 getAbsTransformMatrix() const;

// AActor
  // TODO:

  // vector<shared_ptr<AComp>> comps;
  unordered_map<type_index, shared_ptr<AComp>> comps;

  unsigned int id = getId();
  string name = "";
  virtual string getActorClassName();

  virtual void init();
  virtual void update(const float& dt);

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

  ~Actor();

  void setName (std::string name);

  // its cloning actor and all its components
  // virtual void clone() {
  //   auto actor = make_shared<Actor>();
  //   for (auto& [type, comp] : comps) {
  //     actor->comps[type] = comp->clone();
  //   }
  //   return actor;
  // };
};
