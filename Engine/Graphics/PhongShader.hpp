#pragma once
#include "Shader.hpp"
#include <memory>

class PhongShader : public Shader {
public:
  static PhongShader& get() {
    static PhongShader instance;
    return instance;
  }


  static std::shared_ptr<PhongShader> getPtr() {
    static std::shared_ptr<PhongShader> instancePtr(&get(), [](PhongShader*) {
        // Custom deleter does nothing to prevent deleting singleton
    });
    return instancePtr;
  }

  PhongShader (): Shader(
    Shader::Opts{ .vertPath = "shaders/pos-norm.vert.glsl", .fragPath = "shaders/phong.frag.glsl" }
  ) {

  }
};
