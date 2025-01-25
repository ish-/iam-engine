#pragma once
#include "Graphics/Shader.hpp"

class PhongShader : public Shader {
public:
  static PhongShader& get() {
    static PhongShader instance;
    return instance;
  }

  PhongShader (): Shader(
    (Shader::Opts){ .vertPath = "shaders/pos-norm.vert.glsl", .fragPath = "shaders/phong.frag.glsl" }
  ) {

  }
};
