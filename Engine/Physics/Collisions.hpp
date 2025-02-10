// #include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btCompoundShape.h>
#include <BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <BulletCollision/Gimpact/btGImpactShape.h>
#include "../Graphics/Geo.hpp"

class Collisions {
public:
  static btCompoundShape *createTriMeshShapeCompaund(const Geo::Data &data) {
    btCompoundShape* compoundShape = new btCompoundShape();
    for (size_t i = 0; i < data.meshesOffsets.size(); i++) {
      auto& offset = data.meshesOffsets[i];
      auto& vertices = data.vertices;

      btTriangleMesh *triangleMesh = new btTriangleMesh();
      for (size_t j = i * data.stride; j < data.indices.size(); j += data.stride) {
        btVector3 vertex0(vertices[j + 0], vertices[j + 1], vertices[j + 2]);
        btVector3 vertex1(vertices[j + 3], vertices[j + 4], vertices[j + 5]);
        btVector3 vertex2(vertices[j + 6], vertices[j + 7], vertices[j + 8]);
        triangleMesh->addTriangle(vertex0, vertex1, vertex2);
      }

      btBvhTriangleMeshShape* trimeshShape = new btBvhTriangleMeshShape(triangleMesh, true);
      compoundShape->addChildShape(btTransform::getIdentity(), trimeshShape);
    }

    return compoundShape;
  }

  static btTriangleMesh* createTriangleMesh (const Geo::Data &data) {
    btTriangleMesh *triangleMesh = new btTriangleMesh();

    for (size_t i = 0; i < data.indices.size(); i += 3) {
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
    return triangleMesh;
  }

  static btGImpactMeshShape *createTriGImpactMeshShape(const Geo::Data &data) {
    auto* shape = new btGImpactMeshShape(createTriangleMesh(data));
    shape->updateBound();
    return shape;
  }

  static btBvhTriangleMeshShape *createTriMeshShape(const Geo::Data &data) {
    auto* shape = new btBvhTriangleMeshShape(createTriangleMesh(data), true);
    shape->buildOptimizedBvh();
    return shape;
  }

  static btCompoundShape* createCompauntConvexShape(const Geo::Data& data) {
    btCompoundShape* compoundShape = new btCompoundShape();
    for (size_t i = 0; i < data.meshesOffsets.size(); i++) {
      auto& offset = data.meshesOffsets[i];
      auto& vertices = data.vertices;

      btConvexHullShape* convexShape = new btConvexHullShape();
      // TODO: layout!!
      for (size_t j = i * data.stride; j < data.indices.size(); j += data.stride) {
          convexShape->addPoint(btVector3(vertices[j + 0], vertices[j + 1], vertices[j + 2]));
      }

      compoundShape->addChildShape(btTransform::getIdentity(), compoundShape);
    }

    return compoundShape;
  }
};
