#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> // For quaternion utilities
#include <iostream>

// SLERP function
glm::quat slerp(const glm::quat& q1, const glm::quat& q2, float t) {
    // Ensure t is clamped between 0 and 1
    t = glm::clamp(t, 0.0f, 1.0f);

    // Compute the dot product (cosine of the angle)
    float dot = glm::dot(q1, q2);

    // If the dot product is negative, slerp won't take the shorter path.
    // Invert one quaternion to correct this.
    glm::quat q2_corrected = (dot < 0.0f) ? -q2 : q2;

    // Recalculate the dot product after possible inversion
    dot = glm::dot(q1, q2_corrected);

    // Use linear interpolation if the angle is small to avoid precision issues
    if (dot > 0.9995f) {
        glm::quat result = glm::mix(q1, q2_corrected, t);
        return glm::normalize(result); // Normalize to ensure it's a unit quaternion
    }

    // Calculate the angle between the quaternions
    float theta_0 = glm::acos(dot); // Initial angle
    float theta = theta_0 * t;      // Interpolated angle

    // Compute orthogonal basis
    glm::quat q_perpendicular = glm::normalize(q2_corrected - q1 * dot);

    // Compute the final slerp quaternion
    return q1 * glm::cos(theta) + q_perpendicular * glm::sin(theta);
}

// int main() {
//     // Example usage
//     glm::quat q1 = glm::angleAxis(glm::radians(0.0f), glm::vec3(0, 1, 0)); // Identity rotation
//     glm::quat q2 = glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0)); // 90-degree rotation around Y-axis

//     float t = 0.5f; // Interpolation factor (50%)
//     glm::quat result = slerp(q1, q2, t);

//     std::cout << "SLERP Result (x, y, z, w): "
//               << result.x << ", "
//               << result.y << ", "
//               << result.z << ", "
//               << result.w << std::endl;

//     return 0;
// }