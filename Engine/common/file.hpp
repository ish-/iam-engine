#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "LOG.hpp"

inline std::string loadFile(std::string filePath)
{
  LOG("Reading file", filePath.c_str());
  std::string content;
  std::ifstream fileStream(filePath, std::ios::in);
  if (fileStream.is_open()) {
    std::stringstream sstr;
    sstr << fileStream.rdbuf();
    content = sstr.str();
    fileStream.close();
  } else {
    LOG("Impossible to open", filePath.c_str());
    getchar();
    return "0";
  }
  return content;
}

// const char* filePath = "example.txt";
//     size_t fileSize = 0;

//     // Load the file into memory
//     void* fileData = SDL_LoadFile(filePath, &fileSize);
//     if (!fileData) {
//         std::cerr << "SDL_LoadFile Error: " << SDL_GetError() << std::endl;
//         SDL_Quit();
//         return 1;
//     }

//     // Output the file size and content
//     std::cout << "Loaded file size: " << fileSize << " bytes" << std::endl;
//     std::cout << "File content: " << std::string((char*)fileData, fileSize) << std::endl;

//     // Free the allocated memory
//     SDL_free(fileData);

// #include <SDL3/SDL_iostream.h>

// bool saveFile (const char* filePath, const char* dataToSave) {
//   size_t dataSize = strlen(dataToSave);

//   if (SDL_SaveFile(filePath, dataToSave, dataSize) != 0) {
//       std::cerr << "SDL_SaveFile Error: " << SDL_GetError() << std::endl;
//       SDL_Quit();
//       return 1;
//   }

//   std::cout << "File saved successfully to: " << filePath << std::endl;
// }

// std::vector<char> readFile(const std::string &filepath)
// {
//     std::ifstream file{filepath, std::ios::ate | std::ios::binary};

//     if (!file.is_open())
//     {
//         throw std::runtime_error("failed to open file: " + filepath);
//     }

//     size_t fileSize = static_cast<size_t>(file.tellg());
//     std::vector<char> buffer(fileSize);

//     file.seekg(0);
//     file.read(buffer.data(), fileSize);

//     file.close();
//     return buffer;
// }