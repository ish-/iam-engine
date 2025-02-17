#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
#include <vector>
#include "ModelData.hpp"

class Geo {
public:
  GLuint VAO = 0;
  GLuint VBO = 0;
  GLuint EBO = 0;
  sp<ModelData> data;

  // std::vector<std::shared_ptr<Geo>> parts;

  GLuint vertexCount = 0;

  Geo () {}

  Geo(const sp<ModelData>& data_): data(data_) {
    bindBuffers(*data.get());
  }

  Geo(const sp<ModelData>&& data_): data(data_) {
    bindBuffers(*data.get());
  }

  void bindBuffers(const ModelData& data);

  void clearData();

  ~Geo();
};
