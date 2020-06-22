#ifndef WEIGHT_ENGINE__PHYSICS__PHYSICS_ENGINE_H
#define WEIGHT_ENGINE__PHYSICS__PHYSICS_ENGINE_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>

#include <box2d/box2d.h>

namespace WeightEngine{
  namespace Physics{
    struct WEIGHT_API WorldSetup{

    };
    class WEIGHT_API PhysicsEngine{
      b2World world;
      b2Vec2 gravity;

    public:
      PhysicsEngine();
      ~PhysicsEngine();

      void update(float ts);
    };
  }
}

#endif
