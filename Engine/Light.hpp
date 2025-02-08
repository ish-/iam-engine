#pragma   once
#include "Actor.hpp"
#include "common/json.hpp"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class Light : public Actor {
public:
  float intensity = 1.f;
  glm::vec3 color = {1.0f, 1.0f, 1.0f};
  glm::vec2 attenuation = {8.f, 21.f};

  JSON_DEFINE_OPTIONAL(Light, intensity, color, attenuation)
};