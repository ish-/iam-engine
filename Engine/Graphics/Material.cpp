#include "Material.hpp"

UniformsMap Material::defaultUniforms = UniformsMap{
  {"uWorldAlignedTexture", false},
  {"uUvScale", 1.f},
  {"uNormalOffset", 0.f},
  {"uNormalStrength", 1.f},

  {"sAlbedo", nullptr},
};
