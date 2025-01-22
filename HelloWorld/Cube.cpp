#include "Cube.hpp"
#include <memory>
#include "../util/LOG.hpp"
#include "../Engine/Geo.hpp"
#include "../Engine/Shader.hpp"
using namespace std;

Cube::Cube () {
  ShaderOpts shaderOpts { .vertPath = "shaders/pos-norm.vert.glsl", .fragPath = "shaders/const-norm.frag.glsl" };
  shader = make_shared<Shader>(shaderOpts);
  geo = make_shared<Geo>();
}
// Cube::~Cube () {}

void Cube::update (){
  LOG("Cube update");
}