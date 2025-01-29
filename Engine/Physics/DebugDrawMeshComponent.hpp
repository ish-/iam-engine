#pragma once
#include <memory>
#include <vector>
#include "../Graphics/MeshComponent.hpp"
#include "../Graphics/WireframeShader.hpp"
#include "../Graphics/Geo.hpp"

class DebugDrawGeo : public Geo {
public:
  struct Line { // vertex actually
    glm::vec3 pos;
    // glm::vec3 end;
    // glm::vec3 color;
  };

  unsigned int maxLines = 50000;

  DebugDrawGeo () {
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
};

class DebugDrawMeshComponent : public MeshComponent {
public:
  DebugDrawMeshComponent () {
    shader = WireframeShader::get();
    geo = std::make_shared<DebugDrawGeo>();
    wireframe = true;
  }

  std::vector<DebugDrawGeo::Line> lines;

  virtual void draw () override {
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
};
