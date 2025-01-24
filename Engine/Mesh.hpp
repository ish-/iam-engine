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
  using Ptr = shared_ptr<Mesh>;
  Mesh() {}
  Mesh(const Mesh& mesh) : shader(mesh.shader), geo(mesh.geo), tint(mesh.tint) {}
  Mesh(const shared_ptr<Geo>& geo, const shared_ptr<Shader>& shader) : shader(shader), geo(geo) {}

  shared_ptr<Shader> shader;
  shared_ptr<Geo> geo;
  glm::vec3 tint = glm::vec3(1.);
  bool visible = true;
  bool shaded = true;
  bool wireframe = false;

  template<typename T>
  shared_ptr<T> clone() const {
    static_assert(is_base_of<Mesh, T>::value, "T must be derived from Mesh");
    return make_shared<T>(static_cast<const T&>(*this));
  }

  virtual void draw();
  // virtual void update();
};
