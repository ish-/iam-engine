#pragma once
#include "Material.hpp"
#include "PhongShader.hpp"

struct PhongMaterial : public Material {
  static PhongMaterial& get() {
    static PhongMaterial instance;
    return instance;
  }

  static std::shared_ptr<PhongMaterial> getPtr() {
    static std::shared_ptr<PhongMaterial> instancePtr(&get(), [](PhongMaterial*) {
        // Custom deleter does nothing to prevent deleting singleton
    });
    return instancePtr;
  }

  PhongMaterial(): Material(Material::Conf{
    .albedoPath = "images/grey_grid.png",
  }) {
    shader = PhongShader::getPtr();
  }

  virtual void bind() {
    if (albedoTex) {
      albedoTex->bind(0);

      GLint loc = glGetUniformLocation(shader->shaderId, "sAlbedo");
      glUniform1i(loc, 0);
    }
  }
};