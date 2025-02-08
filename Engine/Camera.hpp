#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Actor.hpp"
#include "common/json.hpp"

class Camera: public Actor {
public:
  struct Conf {
    float ratio = 1.6777;
    float fov = 60;
    float near = .1;
    float far = 1000.;
    bool active = false;

    JSON_DEFINE_OPTIONAL(Conf, ratio, fov, near, far, active)
  };

  Conf conf;

  Camera (): Actor() { }
  Camera (const Conf& conf): conf(conf), Actor() { }

  virtual void init () override {
    setProjection();

    auto scene = getScene();
    bool toSetCamera = false;
    if (!scene->camera)
      toSetCamera = true;
    else if (conf.active) {
      if (scene->camera->conf.active)
        LOG("Warning: multiple active cameras");
      else
        toSetCamera = true;
    }

    if (toSetCamera)
      setActive();
  }

  void setActive () {
    auto scene = getScene();
    if (scene->camera)
      scene->camera->conf.active = false;
    conf.active = true;
    scene->camera = dynamic_pointer_cast<Camera>(shared_from_this());
  }

  glm::mat4 projection;

  void setProjection () {
    projection = glm::perspective(
      glm::radians(conf.fov),
      conf.ratio,
      conf.near,
      conf.far);
  }

  void setRatio (float _ratio) {
    conf.ratio = _ratio;
    setProjection();
  }
};
