#include "DebugDrawMeshComponent.hpp"
#include <glad/glad.h>
#include "../Graphics/WireframeShader.hpp"

DebugDrawGeo::DebugDrawGeo () {
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, maxLines * sizeof(Line), nullptr, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Line), (void*)0);
  // glEnableVertexAttribArray(1);
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Line), (void*)offsetof(Line, end));
  // glEnableVertexAttribArray(2); // Color
  // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Line), (void*)offsetof(Line, color));

  glBindVertexArray(0);
}

DebugDrawMeshComponent::DebugDrawMeshComponent () {
  shader = WireframeShader::get();
  geo = std::make_shared<DebugDrawGeo>();
  wireframe = true;
}

void DebugDrawMeshComponent::draw () {
  glBindBuffer(GL_ARRAY_BUFFER, geo->VBO);
  // if (auto err = glGetError())
  //     LOG("GL ERROR: glBindBuffer", err);
  glBufferSubData(GL_ARRAY_BUFFER, 0, lines.size() * sizeof(DebugDrawGeo::Line), lines.data());
  // if (auto err = glGetError())
  //     LOG("GL ERROR: glBufferSubData", err);

  glBindVertexArray(geo->VAO);
  // if (auto err = glGetError())
  //     LOG("GL ERROR: glBindVertexArray", err);
  glDrawArrays(GL_LINES, 0, lines.size()); // 2 vertices per line
  // if (auto err = glGetError())
  //     LOG("GL ERROR: glDrawArrays", err);
  // glDrawArrays(GL_LINES, 0, lines.size());
  glBindVertexArray(0);
  // if (auto err = glGetError())
  //     LOG("GL ERROR: glBindVertexArray(0)", err);

  lines.clear();
}

