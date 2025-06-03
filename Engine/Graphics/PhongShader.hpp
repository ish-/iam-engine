#pragma once
#include "Shader.hpp"
#include <memory>

class PhongShader : public Shader {
public:
  SINGLETON_PTR(PhongShader)

  PhongShader (): Shader(
    (Shader::Opts){ .vertPath = "shaders/pos-norm.vert.glsl", .fragPath = "shaders/phong.frag.glsl" }
  ) {
  }
};
