#pragma once
#include <nlohmann/json.hpp>
// TODO: try to use forward declaration
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
using namespace nlohmann;

#define JSON_FROM_OPTIONAL(v1) if (nlohmann_json_j.contains(#v1)) nlohmann_json_j.at(#v1).get_to(nlohmann_json_t.v1);
#define JSON_DEFINE_OPTIONAL(Type, ...) \
  friend void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
  friend void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(JSON_FROM_OPTIONAL, __VA_ARGS__)) }

namespace glm {
  static void to_json(nlohmann::json& j, const glm::vec3& v) { j = nlohmann::json{v.x, v.y, v.z};}
  static void from_json(const nlohmann::json& j, glm::vec3& v) { j[0].get_to(v.x); j[1].get_to(v.y); j[2].get_to(v.z); }

  static void to_json(nlohmann::json& j, const glm::vec2& v) { j = nlohmann::json{v.x, v.y};}
  static void from_json(const nlohmann::json& j, glm::vec2& v) { j[0].get_to(v.x); j[1].get_to(v.y); }
}