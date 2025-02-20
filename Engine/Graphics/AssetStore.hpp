#pragma once
#include "ModelData.hpp"

class Geo;

class AssetStore {
public:
  SINGLETON(AssetStore);

  AssetStore ();

  sp<Geo> loadModel (const std::string& path);

  void logChildren (const class aiNode* node, int level = 0);

private:
  std::unordered_map<std::string, sp<Geo>> geos;
  // unordered_map<sp<Geo>> textures;
};
