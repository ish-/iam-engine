#pragma once
#include "PhongShader.hpp"
#include "MeshComp.hpp"
#include "Geo.hpp"
#include <iostream>
#include <glad/glad.h>
#include "../common/LOG.hpp"
#include "../common/json.hpp"
// #include <assimp/Logger.hpp>
// #include <assimp/LogStream.hpp>
// #include <assimp/DefaultLogger.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>

class MeshModelComp : public MeshComp {
public:
  struct Conf : public MeshComp::Conf {
    string path = "";
    bool merge = false;
    bool exposeData = false;

    JSON_DEFINE_OPTIONAL(Conf, path, merge, exposeData)
  };

  virtual Symbol getASystemType () override;

  Conf conf;

  MeshModelComp() : MeshComp() {};
  MeshModelComp (const Conf&& _conf): conf(_conf), MeshComp() {
    // shader = PhongShader::getPtr();

    if (conf.path.length() > 0)
      load(conf.path);
  };

  void logChildren (const aiNode* node, int level = 0);

  bool load (const string& path);
};
