#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "Object3D.hpp"

class Camera: public Object3D {
public:
  struct Conf {
    float ratio = 1.6777;
    float fov = 60;
    float near = .1;
    float far = 1000.;
  };

  glm::mat4 projection;

  Conf params;

  Camera(const Conf&& params): params(params) { setConf(params); }
  // Camera(const Conf& params): params(params) { setConf(params); }

  void setConf (const Conf& params) {
    projection = glm::perspective(
      glm::radians(params.fov),
      params.ratio,
      params.near,
      params.far);
  }

  void setRatio (float ratio) {
    params.ratio = ratio;
    setConf(params);
  }
};
