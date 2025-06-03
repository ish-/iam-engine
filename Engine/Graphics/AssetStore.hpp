#pragma once
#include "ModelData.hpp"

class Geo;
class Texture;
class Material;

struct ModelDataFull {
  sp<Geo> geo;
  sp<Material> material;
};

class AssetStore {
public:
  SINGLETON(AssetStore);

  AssetStore ();

  sp<ModelDataFull> loadModel (const std::string& path);
  sp<Texture> loadTexture (const std::string& path, int numChannels = 4);

  template <typename MAT>
  sp<MAT> createMaterial(const std::string& name, const MAT::Conf& conf) {
    if (materials.find(name) != materials.end())
      return std::dynamic_pointer_cast<MAT>(materials[name]);

    auto material = std::make_shared<MAT>(conf);
    materials[name] = material;
    return material;
  }

  void logChildren (const class aiNode* node, int level = 0);

private:
  std::unordered_map<std::string, sp<Geo>> geos;
  std::unordered_map<std::string, sp<Texture>> textures;
  std::unordered_map<std::string, sp<Material>> materials;
  // unordered_map<sp<Geo>> textures;
};
