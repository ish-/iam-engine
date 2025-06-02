#pragma once

enum GeoAttr {
  POS = 0, UV = 2, COLOR = 7, NORMAL = 1, TANGENT = 3, BITANGENT = 4,
  COUNT = 6 };

constexpr static std::array<std::pair<GeoAttr, GLuint>, GeoAttr::COUNT> ATTR_SIZE_PAIRS = {{
  {POS, 3},
  {UV, 2},
  {COLOR, 4},
  {NORMAL, 3},
  {TANGENT, 3},
  {BITANGENT, 3}
}};

constexpr GLuint attrSize(GeoAttr attr) {
  for (auto& [key, value] : ATTR_SIZE_PAIRS) {
    if (key == attr)
      return value;
  }
  return 0; // or throw if supported in constexpr
}
