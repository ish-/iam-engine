#pragma once
#include <optional>
#include "Material.hpp"
#include "PhongShader.hpp"

struct PhongMaterial : public Material {
  SINGLETON_PTR(PhongMaterial)

  struct Conf : public Material::Conf {
    float shininess = 32.0f;
    glm::vec3 specularColor = { .2f, .2f, .2f };

    JSON_DEFINE_OPTIONAL(Conf, shininess, specularColor);
  };

  Conf conf;

  PhongMaterial(const Material::Conf& conf = {}) : Material(Material::Conf{
    .albedoPath = conf.albedoPath.empty() ? "images/grey_grid.png" : conf.albedoPath,
  }) {
    shader = PhongShader::getPtr();
  }

  virtual void bind() {
    shader->setUniform("uShininess", conf.shininess);
    shader->setUniform("uSpecularColor", conf.specularColor);

    if (albedoTex) {
      albedoTex->bind(0);

      GLint loc = glGetUniformLocation(shader->shaderId, "sAlbedo");
      glUniform1i(loc, 0);
    }

    Material::bind();
  }
};