#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>
#include <vector>
#include "Transform.hpp"

using namespace glm;

class Object3D : public Transform, public std::enable_shared_from_this<Object3D> {
protected:
  std::weak_ptr<Object3D> parent;
public:
  std::vector<std::shared_ptr<Object3D>> children;

  void attach(const Object3D& child);
  void attach(const std::shared_ptr<Object3D>& child);
  std::shared_ptr<Object3D> getParent() const;

  mat4 getTransformMatrix() const;
  mat4 getAbsTransformMatrix() const;
};
