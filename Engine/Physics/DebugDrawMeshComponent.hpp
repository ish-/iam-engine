#pragma once
#include <memory>
#include <vector>
#include "../Graphics/MeshComponent.hpp"
#include "../Graphics/Geo.hpp"

class DebugDrawGeo : public Geo {
public:
  struct Line { // vertex actually
    glm::vec3 pos;
    // glm::vec3 end;
    // glm::vec3 color;
  };

  unsigned int maxLines = 50000;

  DebugDrawGeo ();
};

class DebugDrawMeshComponent : public MeshComponent {
public:
  DebugDrawMeshComponent ();

  std::vector<DebugDrawGeo::Line> lines;

  virtual void draw () override;

  virtual ~DebugDrawMeshComponent() = default;
};;
