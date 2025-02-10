#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 screenToWorldDir(float mouseX, float mouseY, int screenWidth, int screenHeight,
                           const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    float ndcX = (2.0f * mouseX) / screenWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * mouseY) / screenHeight;
    glm::vec4 rayClip(ndcX, ndcY, -1.0f, 1.0f);

    // Transform to view space
    glm::mat4 invProj = glm::inverse(projectionMatrix);
    glm::vec4 rayView = invProj * rayClip;
    rayView.z = -1.0f; // Forward direction
    rayView.w = 0.0f;

    // Transform to world space
    glm::mat4 invView = glm::inverse(viewMatrix);
    glm::vec4 rayWorld = invView * rayView;
    glm::vec3 rayDir = glm::normalize(glm::vec3(rayWorld));

    return glm::vec3(rayDir.x, rayDir.y, rayDir.z);
}