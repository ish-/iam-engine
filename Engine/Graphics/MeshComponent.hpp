#pragma once
#include "../ACS/AComponent.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include "../Object3D.hpp"
#include "../../util/Symbol.hpp"

#include <glad/glad.h>
#include "Shader.hpp"
#include "Geo.hpp"

class Shader;
class Geo;

class MeshComponent : public AComponent, public Object3D {
public:
  shared_ptr<Shader> shader;
  shared_ptr<Geo> geo;

  virtual Symbol getASystemType () override {
      static Symbol symbol { "Renderer" };
      return symbol;
  }

  glm::vec3 tint = glm::vec3(1.);
  bool visible = true;
  bool shaded = true;
  bool wireframe = false;

  virtual void draw() {
    glBindVertexArray(geo->VAO);
    shader->setUniform("tintColor", tint);

    glDrawElements(GL_TRIANGLES, geo->vertexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
  }

  void update (float dt) override {

  }

  // TODO: cache it since it's not update()d
  mat4 getAbsTransformMatrix() const {
    if (auto _parent = getOwner()) {
        return _parent->getAbsTransformMatrix() * getTransformMatrix();
    }
    return getTransformMatrix();
  }
};
