#include <WeightEngine/physics/physics_engine.h>

using namespace WeightEngine;
using namespace Physics;

PhysicsEngine::PhysicsEngine(PhysicsWorldSetup* setup){
  gravity=b2Vec2(-setup->gravity.x, -setup->gravity.y);
  world=new b2World(gravity);

  if(setup->ground){
    ground=world->CreateBody(&(setup->ground.body_def));
    ground->CreateFixture(&(setup->ground.box), 0.0f);
  }

  scale_factor=100.0f; //So -1.0f to 1.0f is 200m
}
PhysicsEngine::~PhysicsEngine(){

}

void PhysicsEngine::update(float ts, float* zoom_level){
  scale_factor*=(*(zoom_level));
  world.Step(ts, PHYSICS_VELOCITY_ITERATIONS, PHYSICS_POSITION_ITERATIONS);
}

Vector2D PhysicsEngine::EARTH_GRAVITY={0.0f, 9.81f};
Position2D PhysicsEngine::world_to_pixels(Position2D world){
  return {world.x/scale_factor, world.y/scale_factor};
}
Position2D PhysicsEngine::pixels_to_world(Position2D pixels){
  return {pixels.x*scale_factor, pixels.y*scale_factor};
}

float PhysicsEngine::metres_to_pixels(float metres){
  return metres/scale_factor;
}
float PhysicsEngine::pixels_to_metres(float pixels){
  return pixels*scale_factor;
}

Ground PhysicsEngine::create_ground(Position2D position, Vector2D dimensions){
  Position2D position_world=PhysicsEngine::pixels_to_world(position);
  Vector2D dimensions_metres={PhysicsEngine::pixels_to_metres(dimensions.x), PhysicsEngine::pixels_to_metres(dimensions.y)};

  Ground result;
  result.body_def.position.Set(position_world.x, position_world.y);
  result.box.SetAsBox(dimensions_metres.x, dimensions_metres.y);
  return result;
}
