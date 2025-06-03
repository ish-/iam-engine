#pragma once
#include <optional>
#include "Material.hpp"
#include "PhongShader.hpp"

static UniformsMap PhongMaterialDefaults = UniformsMap{
  { "uShininess", 32.0f },
  { "uSpecularColor", glm::vec3(0.2f, 0.2f, 0.2f) },
};

struct PhongMaterial : public Material {
  SINGLETON_PTR(PhongMaterial)

  PhongMaterial() : Material(PhongMaterialDefaults) {
    shader = PhongShader::getPtr();
  }
  PhongMaterial(const UniformsMap& _uniforms) : PhongMaterial() {
    for (const auto& [key, value] : _uniforms) {
        uniforms.insert_or_assign(key, value);  // Replaces if key exists
    }
  }

  virtual void bind() override {
    Material::bind();

    shader->setUniform("uShininess", uniforms.get("uShininess"));
    shader->setUniform("uSpecularColor", uniforms.get<glm::vec3>("uSpecularColor"));
  }
};