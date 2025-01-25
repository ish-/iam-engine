#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <vector>

class Geo {
  public:
  GLuint vertexCount;
  GLuint vertexArrayId;
  GLuint vertexBuffer;
  GLuint normalBuffer;
  GLuint elementBuffer;
  glm::vec2 size = glm::vec2(0, 0);

  Geo () {

  }

  void bindBuffers(const std::vector<GLfloat>& vertices,
                   const std::vector<GLint>& elements,
                   const std::vector<GLfloat>& normals);

  ~Geo();
};
