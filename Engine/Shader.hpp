#pragma once
#include <SDL3/SDL_filesystem.h>
#include <glad/glad.h>
#include "../util/file.hpp"
#include "../util/LOG.hpp"
#include <string>
using namespace std;

struct ShaderOpts {
  string vertPath;
  string fragPath;
};

class Shader {
public:
  GLuint shaderId;

  Shader (const ShaderOpts& opts) {
    string vertShaderCode = loadFile("resources/" + opts.vertPath);
    string fragShaderCode = loadFile("resources/" + opts.fragPath);

    shaderId = loadShader(vertShaderCode, fragShaderCode);
  }

  GLuint loadShader (string& vertShaderCode, string& fragShaderCode);
};
