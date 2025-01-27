#pragma once
#include <memory>
#include <vector>
#include "../Graphics/MeshComponent.hpp"
#include "../Graphics/WireframeShader.hpp"
#include "../Graphics/Geo.hpp"

class DebugDrawGeo : public Geo {
public:
  struct Line {
    glm::vec3 start;
    glm::vec3 end;
    glm::vec3 color;
  };

  unsigned int maxLines = 50000;

  DebugDrawGeo () {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, maxLines * sizeof(DebugDrawGeo::Line), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DebugDrawGeo::Line), (void*)offsetof(DebugDrawGeo::Line, start));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(DebugDrawGeo::Line), (void*)offsetof(DebugDrawGeo::Line, end));
  }
};

class DebugDrawMeshComponent : public MeshComponent {
public:
  DebugDrawMeshComponent () {
    shader = WireframeShader::get();
    geo = std::make_shared<DebugDrawGeo>();
  }

  virtual void draw (std::vector<DebugDrawGeo::Line> lines) {
    glBindBuffer(GL_ARRAY_BUFFER, geo->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, lines.size() * sizeof(DebugDrawGeo::Line), lines.data());

    glBindVertexArray(geo->VAO);
    // glDrawArrays(GL_LINES, 0, lines.size() * 2); // 2 vertices per line
    glDrawArrays(GL_LINES, 0, lines.size());
    glBindVertexArray(0);
  }
};
