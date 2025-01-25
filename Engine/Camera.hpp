#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "Object3D.hpp"

class Camera: public Object3D {
public:
  glm::mat4 projection;

  Camera(const float& fov, const float& ratio, const float& near, const float& far)
  {
    update(fov, ratio, near, far);
  }

  void update (const float& fov, const float& ratio, const float& near, const float& far) {
    projection = glm::perspective(glm::radians(fov), ratio, near, far);
  }
};
