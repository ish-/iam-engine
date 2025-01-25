#include "Mesh.hpp"
#include <glad/glad.h>
#include "Shader.hpp"
#include "Geo.hpp"

void Mesh::draw() {
  glBindVertexArray(geo->vertexArrayId);
  shader->setUniform("tintColor", tint);

  glDrawElements(GL_TRIANGLES, geo->vertexCount, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}

void Mesh::init () {
  LOG("Mesh::init()");
}