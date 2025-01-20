#pragma once
#include "./Object3D.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera: public Object3D {
public:
  glm::mat4 projection;

  Camera(const float& fov, const float& ratio, const float& near, const float& far)
  {
    projection = glm::perspective(glm::radians(fov), ratio, near, far);
  }
};
