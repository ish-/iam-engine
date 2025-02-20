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

void Geo::bindInstancingBuffer(const std::vector<glm::mat4>& transforms) {
  // Generate and bind the buffer
  bool created = IBO > 0;
  if (!created) {
    glGenBuffers(1, &IBO);
    if (auto err = glGetError()) LOG("GL ERROR: glGenBuffers", err);
  }
  glBindBuffer(GL_ARRAY_BUFFER, IBO);
  if (auto err = glGetError()) LOG("GL ERROR: glBindBuffer", err);

  if (created) {
    glBufferSubData(GL_ARRAY_BUFFER, 0, transforms.size() * sizeof(glm::mat4), transforms.data());
    if (auto err = glGetError()) LOG("GL ERROR: glBufferSubData", err);
  }
  else {
    glBufferData(GL_ARRAY_BUFFER, (transforms.size() + 30) * sizeof(glm::mat4), transforms.data(), GL_DYNAMIC_DRAW);
    if (auto err = glGetError()) LOG("GL ERROR: glBufferData", err);
  }

  if (!created) {
    // Bind the VAO before setting up vertex attribute pointers
    glBindVertexArray(VAO);

    // Set up vertex attribute pointers for the instance data
    // Each matrix takes up 4 attribute locations (one for each row)
    int attrLoc = data.layout.size();
    for (int i = 0; i < 4; i++) {
      glEnableVertexAttribArray(attrLoc + i); // Assume location attrLoc, 4, 5, 6
      if (auto err = glGetError()) LOG("GL ERROR: glEnableVertexAttribArray", err);
      glVertexAttribPointer(attrLoc + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
      if (auto err = glGetError()) LOG("GL ERROR: glVertexAttribPointer", err);
      glVertexAttribDivisor(attrLoc + i, 1); // Update per instance
      if (auto err = glGetError()) LOG("GL ERROR: glVertexAttribDivisor", err);
    }
    if (auto err = glGetError()) LOG("GL ERROR: attrLoc", err);

    // Unbind the VAO after setting up vertex attribute pointers
    glBindVertexArray(0);
  }
}
