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
    float normalStrength = 1.f;

    JSON_DEFINE_OPTIONAL(Conf, albedoPath);
  };

  Conf conf;

  sp<Texture> albedoTex;
  sp<Shader> shader;

  Material (const Conf& conf): conf(conf) {
    if (!conf.albedoPath.empty()) {
      albedoTex = AssetStore::get().loadTexture(conf.albedoPath, 4);
    }
  }
  virtual void bind () {
    shader->setUniform("uWorldAlignedTexture", conf.worldAlignedTexture);
    shader->setUniform("uUvScale", conf.uvScale);
    shader->setUniform("uNormalOffset", conf.normalOffset);
    shader->setUniform("uNormalStrength", conf.normalStrength);

    useTexture(("Albedo"), albedoTex);
  }

  bool useTexture (const string& name, const sp<Texture> texture = nullptr) const {
    bool useTexture = bool(texture);
    GLint loc = shader->getUnformLocation("s" + name);
    shader->setUniform("uUseAlbedo", useTexture);
    if (texture) {
      texture->bind(0);
      glUniform1i(loc, 0);
    }
    return useTexture;
  }
};
