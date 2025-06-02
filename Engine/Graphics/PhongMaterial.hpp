#pragma once
#include <optional>
#include "Material.hpp"
#include "PhongShader.hpp"

struct PhongMaterial : public Material {
  SINGLETON_PTR(PhongMaterial)

  struct Conf : public Material::Conf {
    float shininess;
    glm::vec3 specularColor;

    Conf()
      : shininess(32.0f), specularColor(0.2f, 0.2f, 0.2f)
    {}

    JSON_DEFINE_OPTIONAL(Conf, shininess, specularColor);
  };

  Conf conf;

  PhongMaterial(const PhongMaterial::Conf& conf = PhongMaterial::Conf{}) : Material(conf), conf(conf) {
    shader = PhongShader::getPtr();
  }

  virtual void bind() override {
    Material::bind();

    shader->setUniform("uShininess", conf.shininess);
    shader->setUniform("uSpecularColor", conf.specularColor);
  }
};