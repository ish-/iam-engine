#pragma once
#include <vector>

struct ModelData {
  std::vector<float> vertices;
  std::vector<int> indices;
  std::vector<int> layout = { 3, 3, 2 }; // vertex, normal, uv
  size_t stride = 8;
  std::vector<int> meshesOffsets; // if mesh is split into multiple parts

  // ModelData(const std::vector<float>& vertices, const std::vector<int>& indices, const std::vector<int>& layout, int stride, const std::vector<int>& meshesOffsets)
  // : vertices(vertices), indices(indices), layout(layout), stride(stride), meshesOffsets(meshesOffsets) {}
};
