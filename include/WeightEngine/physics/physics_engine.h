#ifndef WEIGHT_ENGINE__PHYSICS__PHYSICS_ENGINE_H
#define WEIGHT_ENGINE__PHYSICS__PHYSICS_ENGINE_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>

#include <box2d/box2d.h>

namespace WeightEngine{
  namespace Physics{
    struct Ground{
      b2BodyDef body_def;
      b2PolygonShape box;
    };

    struct WEIGHT_API PhysicsWorldSetup{
      WeightEngine::Vector2D gravity;
      Ground ground;
    };
    class WEIGHT_API PhysicsEngine{
    private:
      b2World* world;
      b2Vec2 gravity;

      b2Body* ground;
    public:
      PhysicsEngine(PhysicsWorldSetup* setup);
      ~PhysicsEngine();

      void update(float ts, float* zoom_level);

      static WeightEngine::Position2D world_to_pixels(WeightEngine::Position2D world);
      static WeightEngine::Position2D pixels_to_world(WeightEngine::Position2D pixels);

      static float metres_to_pixels(float metres);
      static float pixels_to_metres(float pixels);

      static Ground create_ground(WeightEngine::Position2D position, WeightEngine::Vector2D dimensions);
      static WeightEngine::Vector2D EARTH_GRAVITY;
      static float scale_factor;
    };
  }
}

#endif
