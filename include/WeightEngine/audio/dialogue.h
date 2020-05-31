#ifndef WEIGHT_ENGINE__AUDIO__DIALOGUE_H
#define WEIGHT_ENGINE__AUDIO__DIALOGUE_H
#include <ALLibraries/alut.h>
#include <ALLibraries/alhelpers.h>
#include <json.h>

#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/audio_utils.h>
#include <WeightEngine/audio/source.h>

#include <string>
#include <vector>
#include <thread>


namespace Weight{
  namespace Audio{
    struct WEIGHT_API DialogueSegment{
      float start_time;
      std::string transcript;
      float end_time;
      float volume;
    };
    class WEIGHT_API Dialogue:public Weight::Audio::Source{
    private:
      std::vector<DialogueSegment> dialogue_segments;
      AudioUtils::SubtitlingSettings* subtitle_settings;
    public:
      Dialogue();
      ~Dialogue();

      void load_dialogue(std::string path, std::string transcript_path);

      void play(std::string dialogue);
      void play(int index);

      static void count(int id, float duration);
      static void subtitle(AudioUtils::SubtitlingSettings* settings, std::string transcript);
    };
  }
}

#endif
