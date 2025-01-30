#pragma once
#include <SDL3/SDL_filesystem.h>
#include <cstdlib>
#include <glad/glad.h>
#include "../common/file.hpp"
#include "../common/LOG.hpp"
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
using namespace std;


class Shader {
public:
  using Ptr = shared_ptr<Shader>;
  struct Opts {
    string vertPath;
    string fragPath;
  };

  Opts opts;

  GLuint shaderId;
  bool invertNormals = false;
  unsigned int frame = 0;

  Shader (const Shader::Opts& opts): opts(opts) {
    string vertShaderCode = loadFile("resources/" + opts.vertPath);
    string fragShaderCode = loadFile("resources/" + opts.fragPath);

    LOG("--- Loading shader");
    shaderId = loadShader(vertShaderCode, fragShaderCode);
    if (!shaderId) {
      exit(EXIT_FAILURE);
    }
    LOG("--- Shader loaded", shaderId);

    // setUniform("invertNormals", invertNormals);
  }

  void setUniform(const char* name, const glm::mat4& value) { glUniformMatrix4fv(getUnformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
  void setUniform(const char* name, const glm::vec3& value) { glUniform3fv(getUnformLocation(name), 1, glm::value_ptr(value)); }
  void setUniform(const char* name, const glm::vec2& value) { glUniform2fv(getUnformLocation(name), 1, glm::value_ptr(value)); }
  void setUniform(const char* name, const float& value) { glUniform1fv(getUnformLocation(name), 1, &value); }
  void setUniform(const char* name, const int& value) { glUniform1iv(getUnformLocation(name), 1, &value); }
  // void setUniform(const char* name, const bool& value) { glUniform1i(getUnformLocation(name), static_cast<int>(value)); }

private:
  GLuint loadShader (string& vertShaderCode, string& fragShaderCode);

  GLint getUnformLocation(const string& name) {
    if (uniformLocations.find(name) == uniformLocations.end()) {
      uniformLocations[name] = glGetUniformLocation(shaderId, name.c_str());
    }
    return uniformLocations[name];
  }

  unordered_map<string, GLint> uniformLocations;
};
