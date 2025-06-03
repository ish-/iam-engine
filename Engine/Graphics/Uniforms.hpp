#pragma once
#include <variant>
#include <optional>
#include "Texture.hpp"

using UniformValue = std::variant<float, int, std::array<float,4>>;
struct Uniform {
  std::string name;
  UniformValue value;
};

class Uniforms {
public:
  // Insert or overwrite a uniform
  void setUniform(const std::string& name, UniformValue val) {
    _uniforms[name] = std::move(val);
  }

  // Insert or overwrite a texture
  void setTexture(const std::string& name, unsigned int gpuHandle) {
    _textures[name] = gpuHandle;
  }

  // Query whether a uniform exists
  bool hasUniform(const std::string& name) const
  {
    return (_uniforms.find(name) != _uniforms.end());
  }
  // Query whether a texture exists
  bool hasTexture(const std::string& name) const
  {
    return (_textures.find(name) != _textures.end());
  }

  // Get a uniform by name. Returns std::optional<UniformValue>.
  std::optional<UniformValue> getUniform(const std::string& name) const {
    auto it = _uniforms.find(name);
    if (it != _uniforms.end())
      return it->second;
    return std::nullopt;
  }

  // Get a texture handle by name. Returns std::optional<unsigned int>.
  std::optional<unsigned int> getTexture(const std::string& name) const {
    auto it = _textures.find(name);
    if (it != _textures.end())
      return it->second;
    return std::nullopt;
  }

  // For debugging, print out all uniforms + textures
  void debugPrint() const {
    std::cout << "  Uniforms:\n";
    for (const auto& [name, val] : _uniforms) {
      std::cout << "    " << name << " = ";
      std::visit([](auto&& v) {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, float> || std::is_same_v<T, int>) {
          std::cout << v;
        } else if constexpr (std::is_same_v<T, std::array<float, 4>>) {
          std::cout << "[";
          for (size_t i = 0; i < v.size(); ++i) {
            std::cout << v[i];
            if (i + 1 < v.size()) std::cout << ", ";
          }
          std::cout << "]";
        }
      }, val);
      std::cout << "\n";
    }

    std::cout << "  Textures:\n";
    for (const auto& [name, handle] : _textures) {
      std::cout << "    " << name << " -> GPU handle " << handle << "\n";
    }
  }

private:
  std::unordered_map<std::string, UniformValue> _uniforms;
  std::unordered_map<std::string, unsigned int> _textures;
};
