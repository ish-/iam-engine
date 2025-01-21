#pragma once
#include "AComponent.hpp"
#include "Object3D.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>

class Shader;
class Geo;

class Mesh : public Object3D {
public:
  std::shared_ptr<Shader> shader;
  std::shared_ptr<Geo> geo;

  virtual glm::mat4 getMatrix() const;

  virtual void draw(glm::mat4 matrix);
  virtual void update();
};
