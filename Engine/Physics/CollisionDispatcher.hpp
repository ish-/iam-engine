#include <iostream>
#include <memory>
#include "BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
#include "BulletCollision/BroadphaseCollision/btOverlappingPairCache.h"
#include "Physics/PhysicsComp.hpp"
#include "PhysicsComp.hpp"

class CollisionDispatcher : public btCollisionDispatcher {
  public:
      CollisionDispatcher(btCollisionConfiguration* config) : btCollisionDispatcher(config) {}

      virtual bool needsCollision(const btCollisionObject* body0, const btCollisionObject* body1) override {
          return true; // Always process collision
      }

      virtual void dispatchAllCollisionPairs(btOverlappingPairCache* pairCache,
                                             const btDispatcherInfo& dispatchInfo,
                                             btDispatcher* dispatcher) override {
          btCollisionDispatcher::dispatchAllCollisionPairs(pairCache, dispatchInfo, dispatcher);

          // Iterate through contact pairs
          btBroadphasePairArray& pairArray = pairCache->getOverlappingPairArray();
          for (int i = 0; i < pairArray.size(); i++) {
              btBroadphasePair& pair = pairArray[i];
              btCollisionObject* colObj0 = static_cast<btCollisionObject*>(pair.m_pProxy0->m_clientObject);
              btCollisionObject* colObj1 = static_cast<btCollisionObject*>(pair.m_pProxy1->m_clientObject);

              std::cout << "Collision detected between objects: "
                << static_cast<PhysicsComp*>(colObj0->getUserPointer())->getOwner()->name
                << " and "
                << static_cast<PhysicsComp*>(colObj1->getUserPointer())->getOwner()->name
                << std::endl;
          }
      }
  };