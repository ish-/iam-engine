#include "AssetStore.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// #include "MeshComp.hpp"
#include "Geo.hpp"

AssetStore::AssetStore () {}

sp<Geo> AssetStore::loadModel(const std::string& path) {
  if (geos.find(path) != geos.end())
    return geos[path];

  std::cout << "Loading model: " << path << std::endl;
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cerr << "Error: " << importer.GetErrorString() << std::endl;
    return nullptr;
  }
  LOG("Model loaded", "Meshes: ", scene->mNumMeshes, "Materials: ", scene->mNumMaterials, "Textures: ", scene->mNumTextures, "Lights: ", scene->mNumLights, "Cameras: ", scene->mNumCameras);
  LOG("Root node", scene->mRootNode->mName.C_Str());
  logChildren(scene->mRootNode);

  // Extract
  std::vector<float> vertices;
  std::vector<int> indices;
  std::vector<int> meshesOffsets;
  GLint indicesOffset = 0;

  for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
      aiMesh* mesh = scene->mMeshes[i];
      meshesOffsets.push_back(indicesOffset);

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
  auto modelData = ModelData{vertices, indices, {3,3,2}, 8, meshesOffsets};
  auto geo = std::make_shared<Geo>(modelData);
  geos[path] = geo;
  // auto geo = std::make_shared<Geo>(Geo::Data{vertices, indices, {3,3,2}, 8, meshesOffsets});
  // if (!conf.exposeData)
  //   geos[path]->clearData();

  // if (conf.expose)
    // geo = modelGeo;
  return geo;
}

void AssetStore::logChildren (const aiNode* node, int level) {
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    auto name = std::string(node->mChildren[i]->mName.C_Str());
    if (name == "off") continue;
    LOG("-- Child", name);
    logChildren(node->mChildren[i], level + 1);
  }
}
