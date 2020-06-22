#ifndef WEIGHT_ENGINE__AUDIO__LISTENER_H
#define WEIGHT_ENGINE__AUDIO__LISTENER_H
#include <ALLibraries/alut.h>
#include <ALLibraries/alhelpers.h>

#include <WeightEngine/utils/utils.h>

namespace WeightEngine{
  namespace Audio{
    class WEIGHT_API Listener{
    private:
      WeightEngine::Position3D position;
      WeightEngine::Vector3D velocity;
    public:
      Listener(float x, float y, float z);
      ~Listener();

      void set_position(float x, float y, float z);
      void set_velocity(float x, float y, float z);

      //Position
      Listener& operator+=(const WeightEngine::Position3D& rhs);
      Listener& operator-=(const WeightEngine::Position3D& rhs);

      //Velocity
      Listener& operator+=(const WeightEngine::Vector3D& rhs);
      Listener& operator-=(const WeightEngine::Vector3D& rhs);
    };
  }
}

#endif
