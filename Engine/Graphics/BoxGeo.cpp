#include "BoxGeo.hpp"
#include <glm/glm.hpp>
#include <vector>

BoxGeo::BoxGeo(float _size)
  {
    size = glm::vec2(_size, _size);
    float s = _size / 2.;

    // clang-format off
    std::vector<GLfloat> vertices = {
// -z
      -s, s, -s, 0.f, 0.f, -1.f,    0.f, 0.f,
      s, s, -s, 0.f, 0.f, -1.f,   1.f, 0.f,
      s, -s, -s, 0.f, 0.f, -1.f,    1.f, 1.f,
      -s, -s, -s, 0.f, 0.f, -1.f,   0.f, 1.f,
// z
      -s, s, s, 0.f, 0.f, 1.f,    0.f, 0.f,
      s, s, s, 0.f, 0.f, 1.f,   1.f, 0.f,
      s, -s, s, 0.f, 0.f, 1.f,    1.f, 1.f,
      -s, -s, s, 0.f, 0.f, 1.f,   0.f, 1.f,
// x
      s, -s, s, 1.f, 0.f, 0.f,    0.f, 0.f,
      s, s, s, 1.f, 0.f, 0.f,   1.f, 0.f,
      s, s, -s, 1.f, 0.f, 0.f,    1.f, 1.f,
      s, -s, -s, 1.f, 0.f, 0.f,   0.f, 1.f,
// -x
      -s, -s, s, -1.f, 0.f, 0.f,    0.f, 0.f,
      -s, s, s, -1.f, 0.f, 0.f,   1.f, 0.f,
      -s, s, -s, -1.f, 0.f, 0.f,    1.f, 1.f,
      -s, -s, -s, -1.f, 0.f, 0.f,   0.f, 1.f,
// y
        s, s, -s, 0.f, 1.f, 0.f,    0.f, 0.f,
        s, s, s, 0.f, 1.f, 0.f,   1.f, 0.f,
      -s, s, s, 0.f, 1.f, 0.f,    1.f, 1.f,
      -s, s, -s, 0.f, 1.f, 0.f,   0.f, 1.f,
// -y
        s, -s, -s, 0.f, -1.f, 0.f,    0.f, 0.f,
        s, -s, s, 0.f, -1.f, 0.f,   1.f, 0.f,
      -s, -s, s, 0.f, -1.f, 0.f,    1.f, 1.f,
      -s, -s, -s, 0.f, -1.f, 0.f,   0.f, 1.f,
    };

    std::vector<GLint> indices = {
      0, 1, 2, 2, 3, 0,
      4, 5, 6, 6, 7, 4,
      8, 9, 10, 10, 11, 8,
      12, 13, 14, 14, 15, 12,
      16, 17, 18, 18, 19, 16,
      20, 21, 22, 22, 23, 20,
    };
    // clang-format on

    boundingBox.min = glm::vec3(-s, -s, -s);
    boundingBox.max = glm::vec3(s, s, s);

    bindBuffers({vertices, indices, {3, 3, 2}});
  }
