#pragma once
#include "Image.hpp"

struct Texture {
  GLuint id;
  sp<Image> image;

  Texture (const std::string& path, int numChannels) {
    image = std::make_shared<Image>(path, numChannels);
    create();
  }

  Texture (sp<Image> image): image(image) {
    create();
  }

  void bind (GLuint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
  }

  void create () {

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload the pixel data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image->width, image->height, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, image->data);

    glGenerateMipmap(GL_TEXTURE_2D);
  }
};
