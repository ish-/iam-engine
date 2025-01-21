#include "MeshComponent.hpp"
#include "AActor.hpp"

glm::mat4 MeshComponent::getMatrix() const {
  return matrix * getOwner()->matrix;
}