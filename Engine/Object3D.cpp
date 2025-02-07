#include "Object3D.hpp"
#include <glm/gtx/quaternion.hpp>
#include "ACS/AComp.hpp"

mat4 Object3D::getAbsTransformMatrix() const {
  if (auto _parent = parent.lock()) {
      return _parent->getAbsTransformMatrix() * getTransformMatrix();
  }
  return getTransformMatrix();
}

void Object3D::init () {

}

// void Object3D::attach(const Object3D& child) {
//   attach(std::make_shared<Object3D>(child));
// }

void Object3D::attach(const std::shared_ptr<Object3D>& child) {
  child->parent = shared_from_this();
  children.push_back(child);
}

std::shared_ptr<Object3D> Object3D::getParent() const {
  return parent.lock();
}

void Object3D::update() {
  for (auto& [type, component] : components) {
    component->update(-1.);
  }
}

Object3D::~Object3D() {
  // std::cout << "~Object3D\n";
  components.clear();
  children.clear();
}

bool Object3D::removeComp(std::shared_ptr<AComp> comp) {
  components[typeid(comp)] = nullptr;
  return true;
};