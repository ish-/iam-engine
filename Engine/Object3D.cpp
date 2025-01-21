#include "Object3D.hpp"
#include <glm/gtx/quaternion.hpp>

using namespace glm;

void Object3D::updateMat() {
  matrix[3] = vec4(position, 1.0f);
}

void Object3D::setScale(const vec3& scale) {
  matrix = glm::scale(mat4(1.0f), scale) * mat4(mat3(matrix));
}
void Object3D::setScale(float scale) {
  setScale(vec3(scale, scale, scale));
}

void Object3D::setPosition(const vec3& _position) {
  matrix[3] = vec4(_position, 1.0f);
  position = _position;
}

vec3 Object3D::getPosition() const {
  return vec3(matrix[3]);
}

void Object3D::translate(const vec3& translation) {
  mat4 translationMat = glm::translate(I_MAT, translation);
  matrix = translationMat * matrix;
  position = vec3(matrix[3]);
}

void Object3D::translateLocal(const vec3& tranlateBy) {
  matrix = glm::translate(matrix, tranlateBy);
}

quat Object3D::getRotation() const {
  mat3 rotMat = mat3(matrix);
  return quat_cast(rotMat);
}
vec3 Object3D::getRotationEul() const {
  return eulerAngles(getRotation());
}

void Object3D::setRotation(const vec3& angles) {
  mat4 rotationX = glm::rotate(I_MAT, angles.x, vec3(1.0f, 0.0f, 0.0f));
  mat4 rotationY = glm::rotate(I_MAT, angles.y, vec3(0.0f, 1.0f, 0.0f));
  mat4 rotationZ = glm::rotate(I_MAT, angles.z, vec3(0.0f, 0.0f, 1.0f));
  mat4 rotationMatrix = rotationZ * rotationY * rotationX;
  vec3 translation = vec3(matrix[3]);
  matrix = glm::translate(I_MAT, translation) * rotationMatrix;
}
void Object3D::setRotationEul(const vec3& eulerAngles) {
  return setRotation(radians(eulerAngles));
}

void Object3D::setRotationLocal(const vec3& angles) {
  vec3 translation = vec3(matrix[3]);
  quat quater = quat(angles);
  mat4 rotMat = toMat4(quater);
  rotMat[3] = vec4(translation, 1.0f);
  matrix = rotMat;
}
void Object3D::setRotationEulLocal(const vec3& eulerAngs) {
  return setRotationLocal(radians(eulerAngs));
}

void Object3D::rotate(const vec3& angles) {
  mat4 rotationX = glm::rotate(I_MAT, angles.x, vec3(1.0f, 0.0f, 0.0f));
  mat4 rotationY = glm::rotate(I_MAT, angles.y, vec3(0.0f, 1.0f, 0.0f));
  mat4 rotationZ = glm::rotate(I_MAT, angles.z, vec3(0.0f, 0.0f, 1.0f));
  mat4 rotationMatrix = rotationZ * rotationY * rotationX;
  matrix = rotationMatrix * matrix;
}
void Object3D::rotateEul(const vec3& eulerAngs) {
  rotate(radians(eulerAngs));
}

void Object3D::rotateLocal(const vec3& angles) {
  quat quater = quat(angles);
  mat4 rotationMatrix = toMat4(quater);
  matrix = matrix * rotationMatrix;
}
void Object3D::rotateEulLocal(const vec3& eulerAngs) {
  rotateLocal(radians(eulerAngs));
}
