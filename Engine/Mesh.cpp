#include "Mesh.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Shader.hpp"
#include "Geo.hpp"
#include "../util/LOG.hpp"
// #include "Shader.hpp"
// #include "Geo.hpp"
// #include "AActor.hpp"

// void Mesh::update() {
//   draw(getMatrix());
// }

glm::mat4 Mesh::getMatrix() const {
  return matrix;
}

void Mesh::draw() {
  // LOG("Mesh::draw()");
  glBindVertexArray(geo->vertexArrayId);

  // int tintColor = glGetUniformLocation(shader->shaderId, "tintColor");
  // glUniform3fv(tintColor, 1, glm::value_ptr(tint));
  shader->setUniform("tintColor", tint);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  shader->setUniform("wireColor", vec3(0,0,0));
  glDrawElements(GL_TRIANGLES, geo->vertexCount, GL_UNSIGNED_INT, 0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  shader->setUniform("wireColor", vec3(1,1,1));
  glDrawElements(GL_TRIANGLES, geo->vertexCount, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}