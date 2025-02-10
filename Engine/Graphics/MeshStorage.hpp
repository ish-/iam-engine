#pragma once

class MeshStorage {
public:
  SINGLETON(MeshStorage);

  MeshStorage ();

  sp<class Geo> loadModel (const std::string& path);

  void logChildren (const class aiNode* node, int level = 0);

private:
  std::unordered_map<std::string, sp<class Geo>> geos;
  // unordered_map<sp<Geo>> textures;
};
