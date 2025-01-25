#pragma once
#include "../ACS/AComponent.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include "../Object3D.hpp"

#include <glad/glad.h>
#include "Shader.hpp"
#include "Geo.hpp"

class Shader;
class Geo;

class MeshComponent : public AComponent, public Object3D {
public:
  shared_ptr<Shader> shader;
  shared_ptr<Geo> geo;

  glm::vec3 tint = glm::vec3(1.);
  bool visible = true;
  bool shaded = true;
  bool wireframe = false;

  void draw() {
    glBindVertexArray(geo->vertexArrayId);
    shader->setUniform("tintColor", tint);

    glDrawElements(GL_TRIANGLES, geo->vertexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
  }

  void update (float dt) override {

  }
};
