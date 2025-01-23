#include "Object3D.hpp"
#include <glm/gtx/quaternion.hpp>

mat4 Object3D::getTransformMatrix() const {
  return matrix;
}

mat4 Object3D::getAbsTransformMatrix() const {
  if (auto _parent = parent.lock()) {
      return _parent->getAbsTransformMatrix() * getTransformMatrix();
  }
  return getTransformMatrix();
}

void Object3D::attach(const Object3D& child) {
  attach(std::make_shared<Object3D>(child));
}

void Object3D::attach(const std::shared_ptr<Object3D>& child) {
  children.push_back(child);
  children.back()->parent = shared_from_this();
}

std::shared_ptr<Object3D> Object3D::getParent() const {
  return parent.lock();
}