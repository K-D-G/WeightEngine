#ifndef WEIGHT_ENGINE__AUDIO__SOURCE_H
#define WEIGHT_ENGINE__AUDIO__SOURCE_H
#include <ALLibraries/alut.h>
#include <ALLibraries/alhelpers.h>

#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/audio_utils.h>

namespace WeightEngine{
  namespace Audio{
    class WEIGHT_API Source{
    private:
      unsigned int id;
      unsigned int buffer_id;

      WeightEngine::Position3D position;
      WeightEngine::Vector3D velocity;
      float volume;
      bool _music;
    public:
      Source(unsigned int buffer, bool music=false);
      Source(bool music=false);
      ~Source();

      void setup(unsigned int buffer);
      void setup(float roll_off, float reference_distance, float max_distance);
      void setup(unsigned int buffer, float roll_off, float reference_distance, float max_distance);

      void play();
      void pause();
      void stop();
      void loop();
      void stop_loop();
      bool is_playing();

      void set_velocity(float x, float y, float z);
      void set_position(float x, float y, float z);
      void set_volume(float vol);
      void set_pitch(float pitch);
      void set_playback_pointer(float ts);

      int get_source_id();


      //Position
      Source& operator+=(const WeightEngine::Position3D& rhs);
      Source& operator-=(const WeightEngine::Position3D& rhs);

      //Velocity
      Source& operator+=(const WeightEngine::Vector3D& rhs);
      Source& operator-=(const WeightEngine::Vector3D& rhs);

      //Volume
      Source& operator+=(const float vol);
      Source& operator-=(const float vol);
    };
  }
}

#endif
