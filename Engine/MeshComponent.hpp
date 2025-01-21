#pragma once
#include "AComponent.hpp"
#include "Mesh.hpp"
#include <glm/gtc/matrix_transform.hpp>

class MeshComponent : public Mesh, public AComponent {
public:
  virtual glm::mat4 getMatrix() const override;
};
