#pragma once
#include "Shader.hpp"
#include "Texture.hpp"
// #include "Uniforms.hpp"

template<typename K, typename T>
class Map : public std::unordered_map<K, T> {
public:
  Map () = default;
  Map (std::initializer_list<std::pair<const K, T>> uniforms)
    : std::unordered_map<K, T>(uniforms) {}

  template<typename V = float>
  V get(const K& name) const {
    try {
      return std::get<V>(std::unordered_map<K, T>::at(name));
    } catch (const std::out_of_range&) {
      throw std::runtime_error("Uniform " + name + " not found");
    } catch (const std::bad_variant_access&) {
      throw std::runtime_error("Uniform " + name + " is not of the requested type");
    }
  }

  void set (const K& key, const T& value) {
    std::unordered_map<K, T>::insert_or_assign(key, value);
  }
};


using UniformValue = std::variant<bool, float, int, glm::vec2, glm::vec3, glm::vec4, sp<Texture>>;
using UniformsMap = Map<string, UniformValue>;
// using TexturesMap = Map<string, sp<Texture>>;

class Material {
public:
  static UniformsMap defaultUniforms;
  // static TexturesMap defaultTextures;

  UniformsMap uniforms;
  // TexturesMap textures;

  sp<Shader> shader;

  Material () {
    uniforms.insert(defaultUniforms.begin(), defaultUniforms.end());
  };

  Material (const UniformsMap& _uniforms): Material() {
    uniforms.insert(_uniforms.begin(), _uniforms.end());
  };

  virtual void bind () {
    shader->setUniform("uWorldAlignedTexture", uniforms.get<bool>("uWorldAlignedTexture"));
    shader->setUniform("uUvScale", uniforms.get("uUvScale"));
    shader->setUniform("uNormalOffset", uniforms.get("uNormalOffset"));
    shader->setUniform("uNormalStrength", uniforms.get("uNormalStrength"));

    useTexture("Albedo", ALBEDO_UNIT, uniforms.get<sp<Texture>>("sAlbedo"));
  }

  bool useTexture (const string& name, const GLuint unit = 0, const sp<Texture>& texture = nullptr) const {
    bool use = !(texture == nullptr);
    GLint loc = shader->getUnformLocation("s" + name);
    shader->setUniform("uUseAlbedo", use);
    if (texture) {
      texture->activate(unit);
      glUniform1i(loc, unit);
    }
    return use;
  }
};
