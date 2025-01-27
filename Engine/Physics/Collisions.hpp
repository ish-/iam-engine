#include <btBulletDynamicsCommon.h>
#include "../Graphics/Geo.hpp"

class Collisions {
public:
  static btBvhTriangleMeshShape *createTriMeshShape(Geo::Data &data) {
    // TODO: clear?
    btTriangleMesh *triangleMesh = new btTriangleMesh();

    for (size_t i = 0; i < data.indices.size(); i += data.stride) {
      btVector3 vertex0(data.vertices[data.indices[i] * data.stride + 0],
                        data.vertices[data.indices[i] * data.stride + 1],
                        data.vertices[data.indices[i] * data.stride + 2]);

      btVector3 vertex1(data.vertices[data.indices[i + 1] * data.stride + 0],
                        data.vertices[data.indices[i + 1] * data.stride + 1],
                        data.vertices[data.indices[i + 1] * data.stride + 2]);

      btVector3 vertex2(data.vertices[data.indices[i + 2] * data.stride + 0],
                        data.vertices[data.indices[i + 2] * data.stride + 1],
                        data.vertices[data.indices[i + 2] * data.stride + 2]);

      triangleMesh->addTriangle(vertex0, vertex1, vertex2);
    }

    return new btBvhTriangleMeshShape(triangleMesh, true);
  }
};
