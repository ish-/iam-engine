#include "Cube.hpp"
#include <memory>
#include "../util/LOG.hpp"
#include "../Engine/Geo.hpp"
#include "../Engine/Shader.hpp"
using namespace std;

Cube::Cube () {
  Shader::Opts shaderOpt { .vertPath = "shaders/pos-norm.vert.glsl", .fragPath = "shaders/phong.frag.glsl" };
  shader = make_shared<Shader>(shaderOpt);
  geo = make_shared<Geo>();
}
// Cube::~Cube () {}

void Cube::update (){
  // LOG("Cube update");
}