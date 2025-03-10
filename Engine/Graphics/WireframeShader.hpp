#pragma once
#include "Shader.hpp"
#include <memory>

class WireframeShader : public Shader {
public:
  static Shader::Ptr get () {
    static Shader::Ptr wfShader = make_shared<Shader>(Shader::Opts{
      .vertPath = "shaders/pos-norm.vert.glsl",
      .fragPath = "shaders/wireframe.frag.glsl"
    });
    return wfShader;
  };
};