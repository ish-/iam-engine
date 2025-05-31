#pragma once

struct BoundingBox {
  glm::vec3 min = {0,0,0};
  glm::vec3 max = {0,0,0};
  glm::vec3 center = {0,0,0};
  float radius = 0;

  BoundingBox() {}
  BoundingBox(const glm::vec3& min_, const glm::vec3& max_): min(min_), max(max_) {}

  void extend(const float& x, const float& y, const float& z) {
    min.x = std::min(min.x, x);
    min.y = std::min(min.y, y);
    min.z = std::min(min.z, z);
    max.x = std::max(max.x, x);
    max.y = std::max(max.y, y);
    max.z = std::max(max.z, z);
  }

  void update () {
    center = (min + max) * 0.5f;
    radius = glm::length(max - center);
  }
};
