#include "AssetStore.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// #include "MeshComp.hpp"
#include "Geo.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "PhongMaterial.hpp"

AssetStore::AssetStore () {}

sp<ModelDataFull> AssetStore::loadModel(const std::string& path) {
  if (geos.find(path) != geos.end())
    return std::make_shared<ModelDataFull>(geos[path], materials[path]);

  std::cout << "Loading model: " << path << std::endl;
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      std::cerr << "Error: " << importer.GetErrorString() << std::endl;
      throw std::runtime_error("Failed to load model: " + path);
  }
  LOG("Model loaded", "Meshes: ", scene->mNumMeshes, "Materials: ", scene->mNumMaterials, "Textures: ", scene->mNumTextures, "Lights: ", scene->mNumLights, "Cameras: ", scene->mNumCameras);
  LOG("Root node", scene->mRootNode->mName.C_Str());
  logChildren(scene->mRootNode);

  for(unsigned int m = 0; m < scene->mNumMeshes; ++m) {
    aiMesh* mesh = scene->mMeshes[m];
    aiMaterial* mat = scene->mMaterials[ mesh->mMaterialIndex ];

    LOG("Mesh", mesh->mName.C_Str(), "has material", mat->GetName().C_Str());

    // 2a. Read simple material colors:
    aiColor3D diffuseColor(0.f,0.f,0.f);
    if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor)) {
        // use diffuseColor.r, .g, .b
    }
    aiColor3D specColor(0.f,0.f,0.f);
    mat->Get(AI_MATKEY_COLOR_SPECULAR, specColor);

    // 2b. Read PBR parameters (for glTF):
    float metallic = 0.f, roughness = 1.f;
    mat->Get(AI_MATKEY_METALLIC_FACTOR, metallic);
    mat->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness);
    LOG("Mesh", mesh->mName.C_Str(), "has metallic", metallic, "and roughness", roughness);


    // 2c. Read texture slots:
    for(aiTextureType type : { aiTextureType_DIFFUSE,
                              aiTextureType_SPECULAR,
                              aiTextureType_NORMALS,
                              aiTextureType_EMISSIVE, })
    {
        unsigned int count = mat->GetTextureCount(type);
        for(unsigned int t = 0; t < count; ++t) {
            aiString path;
            aiTextureMapping mapping;
            unsigned int uvIndex;
            aiTextureMapMode flags;
            float blend;
            aiTextureOp blendOp;
            mat->GetTexture(type, t, &path, &mapping, &uvIndex, &blend, &blendOp, &flags);

            LOG("Mesh", mesh->mName.C_Str(), "has texture", path.C_Str(), "of type", aiTextureTypeToString(type));

            // path.C_Str() is either:
            // - a file path (e.g. "textures/diffuse.png")
            // - an embedded texture ID like "*0"
            // Load it with your image loader:
            //    if path starts with '*' -> use scene->mTextures[id]
            //    else               -> load from disk
        }
    }
}

  // Extract
  std::vector<float> vertices;
  std::vector<int> indices;
  std::unordered_map<GeoAttr, bool> hasAttrs = {};
  std::vector<int> meshesOffsets;
  GLint indicesOffset = 0;

  BoundingBox bb;

  for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
      aiMesh* mesh = scene->mMeshes[i];
      meshesOffsets.push_back(indicesOffset);

      bool hasN = mesh->HasNormals();
      bool hasTB = mesh->HasTangentsAndBitangents();
      bool hasUV = mesh->HasTextureCoords(0);
      bool hasColor = mesh->HasVertexColors(0);
      if (!hasN && !hasUV)
        throw std::runtime_error("Mesh has no normals or texture coordinates, skipping");

      std::string hasStr = (hasN ? "has normals" : "no normals") + std::string(", ") +
                           (hasUV ? "has texture coords" : "no texture coords");
      LOG("Mesh", mesh->mName.C_Str(), hasStr);

      // Process vertices
      for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
          aiVector3D pos = mesh->mVertices[j];

          // Add to the vertices array
          vertices.push_back(pos.x);
          vertices.push_back(pos.y);
          vertices.push_back(pos.z);
          bb.extend(pos.x, pos.y, pos.z);

          if (hasN) {
            aiVector3D normal = mesh->mNormals[j];
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
          }

          if (hasUV) {
            aiVector3D texCoord = mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][j] : aiVector3D(0.0f, 0.0f, 0.0f);
            vertices.push_back(texCoord.x);
            vertices.push_back(texCoord.y);
          }
      }

      // Process indices
      for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
          aiFace face = mesh->mFaces[j];
          for (unsigned int k = 0; k < face.mNumIndices; k++) {
              indices.push_back(indicesOffset + face.mIndices[k]);
          }
      }
      indicesOffset += mesh->mNumVertices;

      if (hasUV) hasAttrs.insert_or_assign(GeoAttr::UV, hasUV);
      if (hasN) hasAttrs.insert_or_assign(GeoAttr::NORMAL, hasN);
      if (hasTB) hasAttrs.insert_or_assign(GeoAttr::TANGENT, hasTB);
      if (hasTB) hasAttrs.insert_or_assign(GeoAttr::BITANGENT, hasTB);
      if (hasColor) hasAttrs.insert_or_assign(GeoAttr::COLOR, hasColor);
  }
  bb.update();

  UniformsMap matConf;

  for (unsigned int i = 0; i < scene->mNumMaterials && i < 1; i++) {
      aiMaterial* material = scene->mMaterials[i];

      // Process textures (Diffuse)
      unsigned int texCount = material->GetTextureCount(aiTextureType_DIFFUSE);
      // for (unsigned int j = 0; j < texCount; j++) {
      for (unsigned int j = 0; j < 1; j++) {
        aiString texturePath;
        if (material->GetTexture(aiTextureType_DIFFUSE, j, &texturePath) == AI_SUCCESS) {
          // Handle texture loading, e.g., using stb_image.h for loading the image
          std::string textureFilePath = texturePath.C_Str();
          std::cout << "Texture path: " << textureFilePath << std::endl;
          matConf["sAlbedo"] = loadTexture("scenes/" + textureFilePath); // Assuming the texture is in the same directory
        }
      }

    }

  auto mat = createMaterial<PhongMaterial>(path, matConf);
  // auto modelGeo
  auto modelData = ModelData{vertices, indices, {3,3,2}, /* hasAttrs,*/ 8, meshesOffsets};
  auto geo = std::make_shared<Geo>(modelData);
  geo->boundingBox = bb;
  geos[path] = geo;
  // auto geo = std::make_shared<Geo>(Geo::Data{vertices, indices, {3,3,2}, 8, meshesOffsets});
  // if (!conf.exposeData)
  //   geos[path]->clearData();

  // if (conf.expose)
    // geo = modelGeo;
  return std::make_shared<ModelDataFull>(geo, mat);
}

void AssetStore::logChildren (const aiNode* node, int level) {
  std::string name = node->mName.C_Str();
  LOG("-- Child", name, node->mMetaData);
  if (name == "off") return;

  if (node->mMetaData != nullptr) {
    for (int i = 0; i < node->mMetaData->mNumProperties; i++) {
      aiString key, value;
      aiMetadataEntry value2 = node->mMetaData->mValues[i];
      node->mMetaData->Get(i, value);
      key = node->mMetaData->mKeys[i].C_Str();
      LOG("meta: ", key.C_Str(), " -> ", value.C_Str(), value2.mData ? value2.mData : "null");
    }
  }
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    logChildren(node->mChildren[i], level + 1);
  }
}

sp<Texture> AssetStore::loadTexture(const std::string& path, int numChannels) {
  if (textures.find(path) != textures.end())
    return textures[path];

  auto texture = std::make_shared<Texture>(path, numChannels);
  textures[path] = texture;
  return texture;
}
