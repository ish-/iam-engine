#pragma once
#include "PhongShader.hpp"
#include "MeshComponent.hpp"
#include "Geo.hpp"
#include <iostream>
#include <glad/glad.h>
#include "../../util/LOG.hpp"
#include <assimp/Importer.hpp>
// #include <assimp/Logger.hpp>
// #include <assimp/LogStream.hpp>
// #include <assimp/DefaultLogger.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>

class MeshModelComp : public MeshComponent {
public:
  struct Conf {
    string path = "";
    bool merge = false;
    bool expose = false;
  };

  virtual Symbol getASystemType () override {
      static Symbol symbol { "Renderer" };
      return symbol;
  }

  Conf conf;

  MeshModelComp() = default;
  MeshModelComp (const Conf&& _conf): conf(_conf) {
    shader = PhongShader::getPtr();

    if (conf.path.length() > 0)
      load(conf.path);
  };

  void logChildren (const aiNode* node, int level = 0) {
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
      auto name = std::string(node->mChildren[i]->mName.C_Str());
      if (name == "off") continue;
      LOG("Child", name);
      logChildren(node->mChildren[i], level + 1);
    }
  }

  bool load (const string& path) {
    std::cout << "Loading model: " << path << std::endl;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      std::cerr << "Error: " << importer.GetErrorString() << std::endl;
      return -1;
    }
    LOG("Model loaded", "Meshes: ", scene->mNumMeshes, "Materials: ", scene->mNumMaterials, "Textures: ", scene->mNumTextures, "Lights: ", scene->mNumLights, "Cameras: ", scene->mNumCameras);
    LOG("Root node", scene->mRootNode->mName.C_Str());
    logChildren(scene->mRootNode);

    // Extract
    std::vector<GLfloat> vertices;
    std::vector<GLint> indices;
    GLint indicesOffset = 0;

    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];

        // Process vertices
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            aiVector3D position = mesh->mVertices[j];
            aiVector3D normal = mesh->mNormals[j];
            aiVector3D texCoord = mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][j] : aiVector3D(0.0f, 0.0f, 0.0f);

            // Add to the vertices array
            vertices.push_back(position.x);
            vertices.push_back(position.y);
            vertices.push_back(position.z);

            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);

            vertices.push_back(texCoord.x);
            vertices.push_back(texCoord.y);
        }

        // Process indices
        for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; k++) {
                indices.push_back(indicesOffset + face.mIndices[k]);
            }
        }
        indicesOffset += mesh->mNumVertices;
    }

    for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* material = scene->mMaterials[i];

        // Process textures (Diffuse)
        unsigned int texCount = material->GetTextureCount(aiTextureType_DIFFUSE);
        for (unsigned int j = 0; j < texCount; j++) {
            aiString texturePath;
            if (material->GetTexture(aiTextureType_DIFFUSE, j, &texturePath) == AI_SUCCESS) {
                // Handle texture loading, e.g., using stb_image.h for loading the image
                std::string textureFilePath = texturePath.C_Str();
                std::cout << "Texture path: " << textureFilePath << std::endl;
            }
        }
    }

    // auto modelGeo
    geo = std::make_shared<Geo>(Geo::Data{vertices, indices, {3,3,2}});

    // if (conf.expose)
      // geo = modelGeo;

    return true;
  }
};
