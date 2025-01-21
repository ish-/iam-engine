#pragma   once
#include "Object3D.hpp"
#include <glm/ext/vector_float3.hpp>

class Light : public Object3D {
public:
  // Light() {}
  Light(
    float intensity = 1.f,
    glm::vec3 color = {1.0f, 1.0f, 1.0f}
  ) :intensity(intensity), color(color) {

  }

  float intensity;
  glm::vec3 color;
};