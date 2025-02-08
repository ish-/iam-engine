#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "Actor.hpp"
#include "common/json.hpp"

class Camera: public Actor {
public:
  float ratio = 1.6777;
  float fov = 60;
  float near = .1;
  float far = 1000.;

  JSON_DEFINE_OPTIONAL(Camera, ratio, fov, near, far)

  glm::mat4 projection;

  Camera() { setProjection(); }

  void setProjection () {
    projection = glm::perspective(
      glm::radians(fov),
      ratio,
      near,
      far);
  }

  virtual void init () override {
    LOG("Camera::init()");
    getScene()->sayHello();
    // dynamic_pointer_cast<MyGame>(getScene()->getGame())->sayHello();
  }

  void setRatio (float _ratio) {
    ratio = _ratio;
    setProjection();
  }
};
