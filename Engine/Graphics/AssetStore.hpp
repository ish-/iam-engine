#pragma once
#include "ModelData.hpp"

class AssetStore {
public:
  SINGLETON(AssetStore);

  AssetStore ();

  sp<ModelData> loadModel (const std::string& path);

  void logChildren (const class aiNode* node, int level = 0);

private:
  std::unordered_map<std::string, sp<ModelData>> geos;
  // unordered_map<sp<Geo>> textures;
};
