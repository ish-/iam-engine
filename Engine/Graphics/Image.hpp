#pragma once
#include <stb_image.h>

struct Image {
  std::string path;
  int width;
  int height;
  int channels;
  unsigned char* data;

  Image(const std::string& path, int numChannels): path(path) {
    data = stbi_load(("resources/" + path).c_str(), &width, &height, &channels, numChannels);

    if (!data) {
      LOG("Failed to load image", path);
      throw std::runtime_error("Failed to load image.");
    }
  }

  ~Image() {
    if (data) {
      stbi_image_free(data);
    }
  }
};
