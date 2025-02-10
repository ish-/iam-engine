#pragma once
#include <string>
#include "glm/fwd.hpp"
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/quaternion.hpp>
// #include "common/json.hpp"

using namespace glm;

const static mat4 I_MAT = mat4(1.f);

class Transform {
public:
  struct Conf {
    vec3 pos = vec3(0);
    vec3 rot = vec3(0);
    vec3 scale = vec3(1);

    friend void to_json(nlohmann::json& j, const Conf& c) {
      j = nlohmann::json{{"pos", c.pos}, {"rot", c.rot}, {"scale", c.scale}};
    }

    friend void from_json(const nlohmann::json& j, Conf& c) {
      if (j.contains("pos")) j.at("pos").get_to(c.pos);
      if (j.contains("rot")) j.at("rot").get_to(c.rot);
      if (j.contains("scale")) j.at("scale").get_to(c.scale);
    }
  };

  Conf conf;

  Transform() = default;
  Transform (const mat4& matrix): matrix(matrix) {}
  Transform (const vec3& pos) { setPosition(pos); }
  Transform (const vec3& pos, const vec3& rot) { setPosition(pos); setRotation(rot); }
  Transform (const vec3& pos, const vec3& rot, const vec3& _scale) { scale(_scale); setPosition(pos); setRotation(rot); }
  Transform (const Conf& _conf) { setTransformConf(_conf); }

  virtual mat4 getTransformMatrix () const;
  quat getForwardQuat() const;
  vec3 getForward() const;

  void setTransformConf (const Conf& _conf);
  Conf getTransformConf() const;

  void scale(const vec3& scale);
  void scale(float scale);
  glm::vec3 getScale() const;

  void setPosition(const vec3& _position);

  vec3 getPosition() const;

  void translate(const vec3& translation);

  void translateLocal(const vec3& tranlateBy);

  quat getRotation() const;
  vec3 getRotationEul() const;

  void setRotation(const vec3& angles, bool updateConf = true);
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
