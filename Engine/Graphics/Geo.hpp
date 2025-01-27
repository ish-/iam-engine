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
    size_t stride = 8;
    std::vector<GLint> meshesOffsets; // if mesh is split into multiple parts
  };

  GLuint VAO = 0;
  GLuint VBO = 0;
  GLuint EBO = 0;
  Data data;

  // std::vector<std::shared_ptr<Geo>> parts;

  GLuint vertexCount = 0;

  Geo () {}

  Geo(const Data&& data_): data(data_) {
    bindBuffers(data);
  }

  void bindBuffers(const Data& data);

  void clearData();

  ~Geo();
};
