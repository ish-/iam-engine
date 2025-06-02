#pragma   once
#include "Actor.hpp"
#include "common/json.hpp"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class Light : public Actor {
public:
  string getActorClassName() override { return "Light"; }
  struct Conf {
    float intensity = 1.f;
    glm::vec3 color = {1.0f, 1.0f, 1.0f};
    glm::vec2 attenuation = {1.f, 5.f};

    JSON_DEFINE_OPTIONAL(Conf, intensity, color, attenuation)
  };

  void init () override {
    Actor::init();

    if (auto scene = getScene()) {
      scene->lights.push_back(std::dynamic_pointer_cast<Light>(shared_from_this()));
    }
  }

  Light (): Actor() { LOG("Light()"); }
  Light (const Conf &conf): conf(conf), Actor() { LOG("Light(conf)"); }

  Conf conf;
};