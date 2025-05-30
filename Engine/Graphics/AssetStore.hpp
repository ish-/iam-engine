#pragma once
#include "ModelData.hpp"

class Geo;
class Texture;

class AssetStore {
public:
  SINGLETON(AssetStore);

  AssetStore ();

  sp<Geo> loadModel (const std::string& path);
  sp<Texture> loadTexture (const std::string& path, int numChannels = 4);

  void logChildren (const class aiNode* node, int level = 0);

private:
  std::unordered_map<std::string, sp<Geo>> geos;
  std::unordered_map<std::string, sp<Texture>> textures;
  // unordered_map<sp<Geo>> textures;
};
