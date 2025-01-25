#include "Transform.hpp"
#include "../util/slerp.hpp"
#include "glm/gtc/quaternion.hpp"

#include <glm/gtx/quaternion.hpp>

using namespace glm;

mat4 Transform::getTransformMatrix() const{
  return matrix;
}

void Transform::updateMat() {
  matrix[3] = vec4(position, 1.0f);
}

void Transform::scale(const vec3& scale) {
  // matrix = glm::scale(mat4(1.0f), scale) * mat4(mat3(matrix));
  matrix = glm::scale(mat4(1.0f), scale) * matrix;
}

void Transform::scale(float _scale) {
  scale(vec3(_scale, _scale, _scale));
}

void Transform::setPosition(const vec3& _position) {
  matrix[3] = vec4(_position, 1.0f);
  position = _position;
}

vec3 Transform::getPosition() const {
  return vec3(matrix[3]);
}

void Transform::translate(const vec3& translation) {
  mat4 translationMat = glm::translate(I_MAT, translation);
  matrix = translationMat * matrix;
  position = vec3(matrix[3]);
}

void Transform::translateLocal(const vec3& tranlateBy) {
  matrix = glm::translate(matrix, tranlateBy);
}

quat Transform::getRotation() const {
  mat3 rotMat = mat3(matrix);
  return quat_cast(rotMat);
}
vec3 Transform::getRotationEul() const {
  return eulerAngles(getRotation());
}

void Transform::setRotation(const vec3& angles) {
  mat4 rotationX = glm::rotate(I_MAT, angles.x, vec3(1.0f, 0.0f, 0.0f));
  mat4 rotationY = glm::rotate(I_MAT, angles.y, vec3(0.0f, 1.0f, 0.0f));
  mat4 rotationZ = glm::rotate(I_MAT, angles.z, vec3(0.0f, 0.0f, 1.0f));
  mat4 rotationMatrix = rotationZ * rotationY * rotationX;
  vec3 translation = vec3(matrix[3]);
  matrix = glm::translate(I_MAT, translation) * rotationMatrix;
}
void Transform::setRotationEul(const vec3& eulerAngles) {
  return setRotation(radians(eulerAngles));
}

void Transform::setRotationLocal(const vec3& angles) {
  vec3 translation = vec3(matrix[3]);
  quat quater = quat(angles);
  mat4 rotMat = toMat4(quater);
  rotMat[3] = vec4(translation, 1.0f);
  matrix = rotMat;
}
void Transform::setRotationEulLocal(const vec3& eulerAngs) {
  return setRotationLocal(radians(eulerAngs));
}

void Transform::rotate(const vec3& angles) {
  mat4 rotationX = glm::rotate(I_MAT, angles.x, vec3(1.0f, 0.0f, 0.0f));
  mat4 rotationY = glm::rotate(I_MAT, angles.y, vec3(0.0f, 1.0f, 0.0f));
  mat4 rotationZ = glm::rotate(I_MAT, angles.z, vec3(0.0f, 0.0f, 1.0f));
  mat4 rotationMatrix = rotationZ * rotationY * rotationX;
  matrix = rotationMatrix * matrix;
}
void Transform::rotateEul(const vec3& eulerAngs) {
  rotate(radians(eulerAngs));
}

// void Transform::rotateSlerp(const vec3& angles, float t) {
//   mat4 originMat = matrix;
//   quat originQuat = quat_cast(mat3(matrix));
//   quat rotateQuat = quat(radians(angles));
//   quat result = slerp(originQuat, rotateQuat * originQuat, t);
//   mat4 rotationMatrix = toMat4(result);
//   matrix = rotationMatrix * matrix;
// }

void Transform::rotateLocal(const vec3& angles) {
  mat4 rotationMatrix = toMat4(quat(angles));
  matrix = matrix * rotationMatrix;
}
void Transform::rotateEulLocal(const vec3& eulerAngs) {
  rotateLocal(radians(eulerAngs));
}

quat Transform::getForward() const {
  return quat_cast(mat3(matrix));
}

void Transform::setMatrix(const mat4& _matrix) { matrix = _matrix; }