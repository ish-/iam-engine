#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

inline std::string loadFile(std::string filePath)
{
  // Read the Vertex Shader code from the file
  std::string content;
  std::ifstream fileStream(filePath, std::ios::in);
  if (fileStream.is_open()) {
    std::stringstream sstr;
    sstr << fileStream.rdbuf();
    content = sstr.str();
    fileStream.close();
  } else {
    printf("Impossible to open %s. Are you in the right directory?\n", filePath.c_str());
    getchar();
    return "0";
  }
  return content;
}

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