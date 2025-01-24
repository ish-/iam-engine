#pragma   once
#include "Object3D.hpp"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class Light : public Object3D {
public:
  Light() = default;
  Light(
    glm::vec3 pos = {0, 0, 0},
    glm::vec3 color = {1.0f, 1.0f, 1.0f},
    glm::vec2 atteniation = {8.f, 21.f}
  ) : color(color), atteniation(atteniation) {

  }

  float intensity = 1.f;
  glm::vec3 color;
  glm::vec2 atteniation;
};