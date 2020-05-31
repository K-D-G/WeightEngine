#ifndef WEIGHT_ENGINE__AUDIO__LISTENER_H
#define WEIGHT_ENGINE__AUDIO__LISTENER_H
#include <ALLibraries/alut.h>
#include <ALLibraries/alhelpers.h>

#include <WeightEngine/utils/utils.h>

namespace Weight{
  namespace Audio{
    class WEIGHT_API Listener{
    private:
      Weight::Position3D position;
      Weight::Vector3D velocity;
    public:
      Listener(float x, float y, float z);
      ~Listener();

      void set_position(float x, float y, float z);
      void set_velocity(float x, float y, float z);

      //Position
      Listener& operator+=(const Weight::Position3D& rhs);
      Listener& operator-=(const Weight::Position3D& rhs);

      //Velocity
      Listener& operator+=(const Weight::Vector3D& rhs);
      Listener& operator-=(const Weight::Vector3D& rhs);
    };
  }
}

#endif
