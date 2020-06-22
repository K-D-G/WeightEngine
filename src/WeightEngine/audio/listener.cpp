#include <WeightEngine/audio/listener.h>

using namespace WeightEngine;
using namespace Audio;

Listener::Listener(float x, float y, float z){
  set_position(x, y, z);
  set_velocity(0, 0, 0);
}
Listener::~Listener(){

}

void Listener::set_position(float x, float y, float z){
  position={x, y, z};
  alListener3f(AL_POSITION, x, y, z);
}
void Listener::set_velocity(float x, float y, float z){
  velocity={x, y, z};
  alListener3f(AL_VELOCITY, x, y, z);
}

//Position
Listener& Listener::operator+=(const Position3D& rhs){
  this->position.x+=rhs.x;
  this->position.y+=rhs.y;
  this->position.z+=rhs.z;
  this->set_position(this->position.x, this->position.y, this->position.z);
  return *this;
}
Listener& Listener::operator-=(const Position3D& rhs){
  this->position.x-=rhs.x;
  this->position.y-=rhs.y;
  this->position.z-=rhs.z;
  this->set_position(this->position.x, this->position.y, this->position.z);
  return *this;
}

//Velocity
Listener& Listener::operator+=(const Vector3D& rhs){
  this->velocity.x+=rhs.x;
  this->velocity.y+=rhs.y;
  this->velocity.z+=rhs.z;
  this->set_velocity(this->velocity.x, this->velocity.y, this->velocity.z);
  return *this;
}
Listener& Listener::operator-=(const Vector3D& rhs){
  this->velocity.x-=rhs.x;
  this->velocity.y-=rhs.y;
  this->velocity.z-=rhs.z;
  this->set_velocity(this->velocity.x, this->velocity.y, this->velocity.z);
  return *this;
}
