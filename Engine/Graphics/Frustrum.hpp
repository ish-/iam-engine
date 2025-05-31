#pragma once

#include "Graphics/Geo.hpp"
struct Plane {
  glm::vec3 normal;
  float distance;

  float distanceToPoint(const glm::vec3& point) const {
    return glm::dot(normal, point) + distance;
  }
};

// class Frustum {
// public:
//   std::array<Plane, 6> planes;

//   void update(const glm::mat4& VP) {
//     const glm::mat4& m = VP;

//     planes[0] = { glm::vec3(m[0][0] + m[0][3], m[1][0] + m[1][3], m[2][0] + m[2][3]), m[3][0] + m[3][3] }; // Left
//     planes[1] = { glm::vec3(m[0][3] - m[0][0], m[1][3] - m[1][0], m[2][3] - m[2][0]), m[3][3] - m[3][0] }; // Right

//     planes[2] = { glm::vec3(m[0][1] + m[0][3], m[1][1] + m[1][3], m[2][1] + m[2][3]), m[3][1] + m[3][3] }; // Bottom
//     planes[3] = { glm::vec3(m[0][3] - m[0][1], m[1][3] - m[1][1], m[2][3] - m[2][1]), m[3][3] - m[3][1] }; // Top

//     planes[4] = { glm::vec3(m[0][2] + m[0][3], m[1][2] + m[1][3], m[2][2] + m[2][3]), m[3][2] + m[3][3] }; // Near
//     planes[5] = { glm::vec3(m[0][3] - m[0][2], m[1][3] - m[1][2], m[2][3] - m[2][2]), m[3][3] - m[3][2] }; // Far



//     for (auto& plane : planes) {
//       float length = glm::length(plane.normal);
//       plane.normal /= length;
//       plane.distance /= length;
//     }
//   }

//   bool isAABBPartiallyInsideFrustum(const BoundingBox& bb) {
//     // glm::vec3 corners[8] = {
//     //   { min.x, min.y, min.z }, { max.x, min.y, min.z },
//     //   { min.x, max.y, min.z }, { max.x, max.y, min.z },
//     //   { min.x, min.y, max.z }, { max.x, min.y, max.z },
//     //   { min.x, max.y, max.z }, { max.x, max.y, max.z }
//     // };

//     // for (const auto& corner : corners) {
//     //   bool inside = true;
//     //   for (const auto& plane : this->planes) {
//     //     if (plane.distanceToPoint(corner) < 0) {
//     //       inside = false;
//     //       break;
//     //     }
//     //   }
//     //   if (inside) return true;
//     // }

//     // return false;

//     glm::vec3 corners[8] = {
//       { bb.min.x, bb.min.y, bb.min.z }, { bb.max.x, bb.min.y, bb.min.z },
//       { bb.min.x, bb.max.y, bb.min.z }, { bb.max.x, bb.max.y, bb.min.z },
//       { bb.min.x, bb.min.y, bb.max.z }, { bb.max.x, bb.min.y, bb.max.z },
//       { bb.min.x, bb.max.y, bb.max.z }, { bb.max.x, bb.max.y, bb.max.z }
//     };

//     for (const auto& plane : planes) {
//       int out = 0;
//       for (const auto& corner : corners) {
//         if (plane.distanceToPoint(corner) < 0) ++out;
//       }
//       if (out == 8) return false; // All corners outside
//     }

//     return true; // Partially or fully inside
//   }
// };

class Frustum {
public:
    std::array<Plane, 6> planes;

    void update(const glm::mat4& VP) {
        const glm::mat4& m = VP;

        // Corrected plane extraction using column vectors
        planes[0] = { glm::vec3(m[0][3] + m[0][0], m[1][3] + m[1][0], m[2][3] + m[2][0]), m[3][3] + m[3][0] }; // Left
        planes[1] = { glm::vec3(m[0][3] - m[0][0], m[1][3] - m[1][0], m[2][3] - m[2][0]), m[3][3] - m[3][0] }; // Right
        planes[2] = { glm::vec3(m[0][3] + m[0][1], m[1][3] + m[1][1], m[2][3] + m[2][1]), m[3][3] + m[3][1] }; // Bottom
        planes[3] = { glm::vec3(m[0][3] - m[0][1], m[1][3] - m[1][1], m[2][3] - m[2][1]), m[3][3] - m[3][1] }; // Top
        // planes[4] = { glm::vec3(m[0][2], m[1][2], m[2][2]), m[3][2] };  // Near (corrected)
        // planes[5] = { glm::vec3(m[0][3] - m[0][2], m[1][3] - m[1][2], m[2][3] - m[2][2]), m[3][3] - m[3][2] }; // Far
        planes[4] = { glm::vec3(m[0][3] + m[0][2], m[1][3] + m[1][2], m[2][3] + m[2][2]), m[3][3] + m[3][2] }; // Near
        planes[5] = { glm::vec3(m[0][3] - m[0][2], m[1][3] - m[1][2], m[2][3] - m[2][2]), m[3][3] - m[3][2] }; // Far

        // Normalize planes
        for (auto& plane : planes) {
            float length = glm::length(plane.normal);
            plane.normal /= length;
            plane.distance /= length;
        }
    }

    bool isAABBPartiallyInsideFrustum(BoundingBox bb) {
        for (const auto& plane : planes) {
            // Get the positive vertex (p-vertex)
            glm::vec3 positive = bb.min;
            if (plane.normal.x >= 0) positive.x = bb.max.x;
            if (plane.normal.y >= 0) positive.y = bb.max.y;
            if (plane.normal.z >= 0) positive.z = bb.max.z;

            // If p-vertex is outside, the entire AABB is outside
            if (plane.distanceToPoint(positive) < 0) {
                return false;
            }
        }
        return true;
    }
};