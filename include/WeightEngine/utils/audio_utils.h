#ifndef WEIGHT_ENGINE__UTILS__AUDIO_UTILS_H
#define WEIGHT_ENGINE__UTILS__AUDIO_UTILS_H
#include <ALLibraries/alut.h>
#include <ALLibraries/alhelpers.h>

#include <WeightEngine/utils/utils.h>
#include <WeightEngine/render_engine/font.h>
#include <WeightEngine/render_engine/text_renderer.h>

#include <string>

#define LINEAR_DISTANCE AL_LINEAR_DISTANCE
#define LINEAR_DISTANCE_CLAMPED AL_LINEAR_DISTANCE_CLAMPED
#define EXPONENT_DISTANCE AL_EXPONENT_DISTANCE
#define EXPONENT_DISTANCE_CLAMPED AL_EXPONENT_DISTANCE_CLAMPED
#define INVERSE_DISTANCE AL_INVERSE_DISTANCE
#define INVERSE_DISTANCE_CLAMPED AL_INVERSE_DISTANCE_CLAMPED

namespace Weight{
  class WEIGHT_API AudioUtils{
  public:
    struct SubtitlingSettings{
      Weight::RenderEngine::TextRenderer* text_renderer;
      bool subtitle;
      Weight::RenderEngine::Font* font;
      Weight::Colour colour;
      float font_size;
    };

  private:
    static float volume;
    static float music_volume;
  public:
    static SubtitlingSettings* subtitle_settings;

    static float get_volume();
    static float get_music_volume();

    static void set_volume(float v);
    static void set_music_volume(float v);

    static void set_subtitling_renderer(Weight::RenderEngine::TextRenderer* text_renderer);
    static void set_subtitling(bool subtitle, Weight::RenderEngine::Font* font=nullptr, Weight::Colour colour={0.0f, 0.0f, 0.0f, 0.0f}, float font_size=20.0f);
    static AudioUtils::SubtitlingSettings* get_subtitling_settings();

    static unsigned int load_sound(std::string file);
    static void set_distance_model(int model);
  };
}

#endif
