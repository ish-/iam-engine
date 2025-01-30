#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include "Transform.hpp"
// #include "ACS/AActor.hpp"
using namespace glm;

class AComponent;

class Object3D : public Transform, public std::enable_shared_from_this<Object3D> {
// Object3D
protected:
  std::weak_ptr<Object3D> parent;
public:
  template<typename... Args>
  Object3D (Args&&... args): Transform(std::forward<Args>(args)...) {}

  std::vector<std::shared_ptr<Object3D>> children;

  // void attach(const Object3D& child);
  void attach(const std::shared_ptr<Object3D>& child);
  std::shared_ptr<Object3D> getParent() const;

  mat4 getAbsTransformMatrix() const;

// AActor
  // TODO:
  std::string name = "Actor";

  std::unordered_map<std::type_index, std::shared_ptr<AComponent>> components;

  virtual void init();
  virtual void update();

  template <typename T>
  std::shared_ptr<T> getComponent() {
      auto it = components.find(typeid(T));
      if (it != components.end()) {
          return std::dynamic_pointer_cast<T>(it->second);
      }
      return nullptr;
  }

  bool removeComponents() {
    components.clear();
    return true;
  };

  bool removeComponent(std::shared_ptr<AComponent> comp) {
    components[typeid(comp)] = nullptr;
    return true;
  };

  ~Object3D() {
    // std::cout << "~Object3D\n";
    removeComponents();
    children.clear();
  }
};
