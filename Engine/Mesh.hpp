#pragma once
// #include "AComponent.hpp"
#include "Object3D.hpp"
#include "WObject.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

class Shader;
class Geo;

class Mesh : public Object3D {
public:
  Mesh() {}
  Mesh(const shared_ptr<Geo>& geo, const shared_ptr<Shader>& shader) : shader(shader), geo(geo) {}

  shared_ptr<Shader> shader;
  shared_ptr<Geo> geo;

  virtual glm::mat4 getMatrix() const;

  virtual void draw(glm::mat4 matrix);
  // virtual void update();
};
