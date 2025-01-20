#include <memory>
#include "AActor.hpp"
#include "AComponent.hpp"
#include "Object3D.hpp"

class MaterialUniforms {
public:
  MaterialUniforms() {
    // Create a buffer for the material uniforms
    SDL_GPUBufferCreateInfo materialBufferCreateInfo = {
      .usage = SDL_GPU_BUFFERUSAGE_UNIFORM,
      .size = sizeof(fragMultiplyUniformCube),
    };
    materialBuffer = renderer.CreateBuffer(materialBufferCreateInfo);
  }

  void setMaterialUniforms(fragMultiplyUniformCube& materialUniforms) {
    renderer.UpdateBuffer(materialBuffer, &materialUniforms, sizeof(fragMultiplyUniformCube));
  }

  SDL_GPUBuffer* materialBuffer{ nullptr };
}

class Material {
public:
  Material();

}
class Geometry;

class IDrawable {
public:
  virtual void draw() = 0;
};

class MeshComp : public AComponent, public IDrawable {
public:
  MeshComp(std::shared_ptr<Geometry>& geo, std::shared_ptr<Material>& mat);

  std::shared_ptr<Geometry> geo;
  std::shared_ptr<Material> mat;

  void draw() override;
};

class ACube : public AActor, public Object3D {
public:
  ACube(AppContext& ctx) : AActor(ctx) {
    addComponent<MeshComp>(
      std::make_shared<Geometry>(),
      std::make_shared<Material>()
    );
  }

  void update() override;

public:

};
