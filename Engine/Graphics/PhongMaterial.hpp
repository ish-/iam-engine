#pragma once
#include "Material.hpp"
#include "PhongShader.hpp"

struct PhongMaterial : public Material {
  SINGLETON_PTR(PhongMaterial)

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