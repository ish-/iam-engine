#pragma once
#include "Shader.hpp"
#include "AssetStore.hpp"
#include "Texture.hpp"

struct Material {
  struct Conf {
    string albedoPath = "";
    bool worldAlignedTexture = false;
    float uvScale = 1.f;
    float normalOffset = 0.f;

    JSON_DEFINE_OPTIONAL(Conf, albedoPath);
  };

  Conf conf;

  sp<Texture> albedoTex;
  sp<Shader> shader;

  Material (const Conf& conf) {
    if (!conf.albedoPath.empty()) {
      albedoTex = AssetStore::get().loadTexture(conf.albedoPath, 4);
    }
  }
  virtual void bind () {
    shader->setUniform("uWorldAlignedTexture", conf.worldAlignedTexture);
    shader->setUniform("uUvScale", conf.uvScale);
    shader->setUniform("uNormalOffset", conf.normalOffset);

    if (albedoTex) {
      albedoTex->bind(0);

      GLint loc = glGetUniformLocation(shader->shaderId, "sAlbedo");
      glUniform1i(loc, 0);
    }
  }
};
