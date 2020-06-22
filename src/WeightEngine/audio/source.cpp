#include <WeightEngine/audio/source.h>

using namespace WeightEngine;
using namespace Audio;

Source::Source(unsigned int buffer, bool music):_music(music){
  alGenSources(1, &id);
  volume=(_music)?AudioUtils::get_music_volume():AudioUtils::get_volume();
  alSourcef(id, AL_GAIN, volume);
  alSourcef(id, AL_PITCH, 1);
  alSource3f(id, AL_POSITION, 0, 0, 0);
  alSource3f(id, AL_VELOCITY, 0, 0, 0);
  position={0, 0, 0};
  velocity={0, 0, 0};


  setup(buffer);

  alSourcef(id, AL_ROLLOFF_FACTOR, 1);
  alSourcef(id, AL_REFERENCE_DISTANCE, 4);
  alSourcef(id, AL_MAX_DISTANCE, 10);
}

Source::Source(bool music):_music(music){
  alGenSources(1, &id);
  volume=(_music)?AudioUtils::get_music_volume():AudioUtils::get_volume();
  alSourcef(id, AL_GAIN, volume);
  alSourcef(id, AL_PITCH, 1);
  alSource3f(id, AL_POSITION, 0, 0, 0);
  alSource3f(id, AL_VELOCITY, 0, 0, 0);
  position={0, 0, 0};
  velocity={0, 0, 0};


  alSourcef(id, AL_ROLLOFF_FACTOR, 1);
  alSourcef(id, AL_REFERENCE_DISTANCE, 4);
  alSourcef(id, AL_MAX_DISTANCE, 10);
}

Source::~Source(){
  stop();
  alDeleteSources(1, &id);
}


void Source::setup(unsigned int buffer){
  stop();
  buffer_id=buffer;
  alSourcei(id, AL_BUFFER, buffer_id);
}

void Source::setup(float roll_off, float reference_distance, float max_distance){
  stop();
  alSourcef(id, AL_ROLLOFF_FACTOR, roll_off);
  alSourcef(id, AL_REFERENCE_DISTANCE, reference_distance);
  alSourcef(id, AL_MAX_DISTANCE, max_distance);
}

void Source::setup(unsigned int buffer, float roll_off, float reference_distance, float max_distance){
  stop();
  buffer_id=buffer;
  alSourcei(id, AL_BUFFER, buffer_id);

  alSourcef(id, AL_ROLLOFF_FACTOR, roll_off);
  alSourcef(id, AL_REFERENCE_DISTANCE, reference_distance);
  alSourcef(id, AL_MAX_DISTANCE, max_distance);
}



void Source::play(){
  alSourcePlay(id);
}
void Source::pause(){
  alSourcePause(id);
}
void Source::stop(){
  alSourceStop(id);
}
void Source::loop(){
  alSourcei(id, AL_LOOPING, AL_TRUE);
}
void Source::stop_loop(){
  alSourcei(id, AL_LOOPING, AL_FALSE);
}
bool Source::is_playing(){
  int value;
  alGetSourcei(id, AL_SOURCE_STATE, &value);
  return value==AL_PLAYING;
}

void Source::set_velocity(float x, float y, float z){
  velocity={x, y, z};
  alSource3f(id, AL_VELOCITY, x, y, z);
}
void Source::set_position(float x, float y, float z){
  position={x, y, z};
  alSource3f(id, AL_POSITION, x, y, z);
}
void Source::set_volume(float vol){
  volume=vol*((_music)?AudioUtils::get_music_volume():AudioUtils::get_volume());
  alSourcef(id, AL_GAIN, vol);
}
void Source::set_pitch(float pitch){
  alSourcef(id, AL_PITCH, pitch);
}

void Source::set_playback_pointer(float ts){
  alSourcef(id, AL_SEC_OFFSET, ts);
}

int Source::get_source_id(){
  return id;
}

//Position
Source& Source::operator+=(const Position3D& rhs){
  this->position.x+=rhs.x;
  this->position.y+=rhs.y;
  this->position.z+=rhs.z;
  this->set_position(this->position.x, this->position.y, this->position.z);
  return *this;
}
Source& Source::operator-=(const Position3D& rhs){
  this->position.x-=rhs.x;
  this->position.y-=rhs.y;
  this->position.z-=rhs.z;
  this->set_position(this->position.x, this->position.y, this->position.z);
  return *this;
}

//Velocity
Source& Source::operator+=(const Vector3D& rhs){
  this->velocity.x+=rhs.x;
  this->velocity.y+=rhs.y;
  this->velocity.z+=rhs.z;
  this->set_velocity(this->velocity.x, this->velocity.y, this->velocity.z);
  return *this;
}
Source& Source::operator-=(const Vector3D& rhs){
  this->velocity.x-=rhs.x;
  this->velocity.y-=rhs.y;
  this->velocity.z-=rhs.z;
  this->set_velocity(this->velocity.x, this->velocity.y, this->velocity.z);
  return *this;
}

//Volume
Source& Source::operator+=(const float vol){
  this->volume+=vol;
  this->set_volume(vol);
  return *this;
}
Source& Source::operator-=(const float vol){
  this->volume-=vol;
  this->set_volume(vol);
  return *this;
}
