#pragma once
#include <string>
#include "glm/fwd.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

const static mat4 I_MAT = mat4(1.f);

class Transform {
public:

  Transform() = default;
  Transform (const mat4& matrix): matrix(matrix) {}
  Transform (const vec3& pos) { setPosition(pos); }
  Transform (const vec3& pos, const vec3& rot) { setPosition(pos); setRotation(rot); }
  Transform (const vec3& pos, const vec3& rot, const vec3& _scale) { scale(_scale); setPosition(pos); setRotation(rot); }

  virtual mat4 getTransformMatrix () const;
  quat getForward() const;

  vec3 position = vec3(0.);

  void updateMat();
  void scale(const vec3& scale);
  void scale(float scale);

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

  // void rotateSlerp(const vec3& angles, float t);

  // mat4 getTransform() const;
  // mat4 getAbsTransform() const;

  void setMatrix(const mat4& _matrix);
  void setMatrix(const mat4&& _matrix);

  std::string transformStr() const;
protected:
  mat4 matrix = I_MAT;
};
