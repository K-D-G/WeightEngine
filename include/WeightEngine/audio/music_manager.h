#ifndef WEIGHT_ENGINE__AUDIO__MUSIC_MANAGER_H
#define WEIGHT_ENGINE__AUDIO__MUSIC_MANAGER_H
#include <ALLibraries/alut.h>
#include <ALLibraries/alhelpers.h>

#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/audio_utils.h>

#include <WeightEngine/audio/listener.h>
#include <WeightEngine/audio/source.h>

#include <string>
#include <unordered_map>

//3D sound will only work with MONO audio and NOT STEREO
namespace Weight{
  namespace Audio{
    class WEIGHT_API MusicManager{
    private:
      Weight::Audio::Source* source;

      std::unordered_map<std::string, unsigned int> music;
    public:
      MusicManager();
      ~MusicManager();

      void load_music(std::string path, std::string shortcut_name);
      void load_music(std::string shortcut_name);

      //We assume that music loops
      void play();
      void pause();
      void stop();

      //void set_volume(float vol);
      void set_pitch(float pitch);
    };
  }
}

#endif
