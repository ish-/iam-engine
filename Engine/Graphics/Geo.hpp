#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
#include <vector>

class Geo {
public:
  struct Data {
    std::vector<GLfloat> vertices;
    std::vector<GLint> indices;
    std::vector<GLint> layout = { 3, 3, 2 }; // vertex, normal, uv
    // std::vector<GLint> meshesOffsets; // if mesh is split into multiple parts
  };

  GLuint VAO;
  Data data;
  // std::vector<std::shared_ptr<Geo>> parts;

  GLuint vertexCount;
  GLuint vertexBuffer;
  GLuint normalBuffer;
  GLuint elementBuffer;
  glm::vec2 size = glm::vec2(0, 0);

  Geo () {}

  Geo(const Data&& data_): data(data_) {
    bindBuffers(data);
  }

  void bindBuffers(const Data& data);

  void bindBuffers(const std::vector<GLfloat>& vertices,
                   const std::vector<GLint>& elements,
                   const std::vector<GLfloat>& normals);

  ~Geo();
};
