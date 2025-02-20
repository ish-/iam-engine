#include "Geo.hpp"
#include "glad/glad.h"
#include <sys/types.h>

void Geo::bindBuffers(const ModelData& data) {
  // GLuint VBO, EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Bind and upload vertex data
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(GLfloat), data.vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(GLint), data.indices.data(), GL_STATIC_DRAW);

  GLuint stride = 0;
  for (auto& layout : data.layout)
    stride += layout;
  vertexCount = data.indices.size();
  stride *= sizeof(GLfloat);

  GLuint VAOffset = 0;
  for (int i = 0; i < data.layout.size(); i++) {
    if (data.layout[i] == 0) continue;
    glVertexAttribPointer(i, data.layout[i], GL_FLOAT, GL_FALSE, stride, (void*)(VAOffset * sizeof(GLfloat)));
    glEnableVertexAttribArray(i);
    VAOffset += data.layout[i];
  }

  glBindVertexArray(0);
}

Geo::~Geo()
{
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
}

void Geo::clearData() {
  data.vertices.clear();
  data.indices.clear();
  data.layout.clear();
}
