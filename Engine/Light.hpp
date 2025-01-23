#pragma   once
#include "Object3D.hpp"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class Light : public Object3D {
public:
  // Light() {}
  Light(
    float intensity = 1.f,
    glm::vec3 color = {1.0f, 1.0f, 1.0f},
    glm::vec2 atteniation = {5.f, 10.f}
  ) :intensity(intensity), color(color), atteniation(atteniation) {

  }

  float intensity;
  glm::vec3 color;
  glm::vec2 atteniation;
};