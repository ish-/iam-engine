#include "Mesh.hpp"
#include "Shader.hpp"
#include "Geo.hpp"
#include "AActor.hpp"

void Mesh::update() {
  draw(getMatrix());
}

glm::mat4 Mesh::getMatrix() const {
  return matrix;
}

void Mesh::draw(glm::mat4 matrix) {
  // glBind
  // glDraw
}