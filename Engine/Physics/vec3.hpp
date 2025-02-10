#include <glm/ext/vector_float3.hpp>
#include <LinearMath/btVector3.h>

inline glm::vec3 operator+(const btVector3& v) {
    return glm::vec3(v.getX(), v.getY(), v.getZ());
}

inline btVector3 operator+(const glm::vec3& v) {
    return btVector3(v.x, v.y, v.z);
}
