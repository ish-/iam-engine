#pragma once
#include <memory>
#include <vector>
#include "../Graphics/MeshComp.hpp"
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

class DebugDrawMeshComp : public MeshComp {
public:
  DebugDrawMeshComp ();

  std::vector<DebugDrawGeo::Line> lines;

  virtual void draw () override;

  virtual ~DebugDrawMeshComp() = default;
};;
