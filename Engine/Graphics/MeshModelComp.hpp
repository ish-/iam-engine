#pragma once
#include "PhongShader.hpp"
#include "MeshComponent.hpp"
#include <iostream>
#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class MeshModelComp : public MeshComponent {
public:
  struct Conf {
    char* path = nullptr;
  };
  Conf conf;

  MeshModelComp() = default;
  MeshModelComp (const Conf&& _conf): conf(_conf) {
    shader = PhongShader::getPtr();
    if (conf.path)
      load(conf.path);
  };

  bool load (const char* path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      std::cerr << "Error: " << importer.GetErrorString() << std::endl;
      return -1;
    }

    // Extract
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

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
                indices.push_back(face.mIndices[k]);
            }
        }
    }

    indicesNum = indices.size();

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

    // bind

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind and upload vertex data
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    return true;
  }

  void draw () {
    // glUseProgram(shaderID);
    shader->setUniform("tintColor", tint);
    // Bind texture if applicable
    // glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicesNum, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

private:
  GLuint VAO, VBO, EBO;
  unsigned int indicesNum;
};
