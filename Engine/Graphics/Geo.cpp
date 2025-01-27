#include "Geo.hpp"
#include "glad/glad.h"
#include <sys/types.h>

void Geo::bindBuffers(const Data& data) {
  GLuint VBO, EBO;

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
  stride *= sizeof(GLfloat);

  GLuint VAOffset = 0;
  for (uint i = 0; i < data.layout.size(); i++) {
    if (data.layout[i] == 0) continue;
    glVertexAttribPointer(i, data.layout[i], GL_FLOAT, GL_FALSE, stride, (void*)(VAOffset * sizeof(GLfloat)));
    glEnableVertexAttribArray(i);
    VAOffset += data.layout[i];
  }

  glBindVertexArray(0);
}

void Geo::bindBuffers(const std::vector<GLfloat>& vertices,
                   const std::vector<GLint>& elements,
                   const std::vector<GLfloat>& normals)
{
  vertexCount = elements.size();

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  glGenBuffers(1, &elementBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLint), elements.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}

Geo::~Geo()
{
  // TODO: VAO erase vectors
  if (VBO) {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
  }

  if (normalBuffer) {
    glDeleteBuffers(1, &normalBuffer);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &elementBuffer);
  }

  glDeleteVertexArrays(1, &VAO);
}
