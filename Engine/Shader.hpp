#pragma once
#include <SDL3/SDL_filesystem.h>
#include <glad/glad.h>
#include "../util/file.hpp"
#include "../util/LOG.hpp"
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

struct ShaderOpts {
  string vertPath;
  string fragPath;
};

class Shader {
public:
  GLuint shaderId;
  bool invertNormals = false;

  Shader (const ShaderOpts& opts) {
    string vertShaderCode = loadFile("resources/" + opts.vertPath);
    string fragShaderCode = loadFile("resources/" + opts.fragPath);

    shaderId = loadShader(vertShaderCode, fragShaderCode);

    // setUniform("invertNormals", invertNormals);
  }


  void setUniform(const char* name, const glm::mat4& value) { glUniformMatrix4fv(glGetUniformLocation(shaderId, name), 1, GL_FALSE, glm::value_ptr(value)); }
  void setUniform(const char* name, const glm::vec3& value) { glUniform3fv(glGetUniformLocation(shaderId, name), 1, glm::value_ptr(value)); }
  void setUniform(const char* name, const glm::vec2& value) { glUniform2fv(glGetUniformLocation(shaderId, name), 1, glm::value_ptr(value)); }
  void setUniform(const char* name, const float& value) { glUniform1fv(glGetUniformLocation(shaderId, name), 1, &value); }
  // void setUniform(const char* name, const bool& value) { glUniform1ui(glGetUniformLocation(shaderId, name), 1, &value); }

  GLuint loadShader (string& vertShaderCode, string& fragShaderCode);
};
