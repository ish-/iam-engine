#pragma once
// #include "AComponent.hpp"
#include "Object3D.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
using namespace std;

class Shader;
class Geo;

class Mesh : public Object3D {
public:
  Mesh() {}
  Mesh(const shared_ptr<Geo>& geo, const shared_ptr<Shader>& shader) : shader(shader), geo(geo) {}

  shared_ptr<Shader> shader;
  shared_ptr<Geo> geo;
  glm::vec3 color = glm::vec3(1, .4, .5);

  virtual glm::mat4 getMatrix() const;

  virtual void draw();
  // virtual void update();
};
