#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

const mat4 I_MAT = mat4(1.f);

class Object3D {
public:
  mat4 matrix = I_MAT;

  vec3 position = vec3(0.);

  void updateMat();
  void setScale(const vec3& scale);
  void setScale(float scale);

  void setPosition(const vec3& _position);

  vec3 getPosition() const;

  void translate(const vec3& translation);

  void translateLocal(const vec3& tranlateBy);

  quat getRotation() const;
  vec3 getRotationEul() const;

  void setRotation(const vec3& angles);
  void setRotationEul(const vec3& eulerAngles);

  void setRotationLocal(const vec3& angles);
  void setRotationEulLocal(const vec3& eulerAngs);
  void rotate(const vec3& angles);
  void rotateEul(const vec3& eulerAngs);

  void rotateLocal(const vec3& angles);
  void rotateEulLocal(const vec3& eulerAngs);
};
