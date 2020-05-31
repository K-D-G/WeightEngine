#include <WeightEngine/utils/audio_utils.h>

using namespace Weight;
using namespace RenderEngine;

float AudioUtils::volume=1.0f;
float AudioUtils::music_volume=1.0f;
AudioUtils::SubtitlingSettings* AudioUtils::subtitle_settings=new AudioUtils::SubtitlingSettings;

float AudioUtils::get_volume(){
  return AudioUtils::volume;
}
float AudioUtils::get_music_volume(){
  return AudioUtils::music_volume;
}

void AudioUtils::set_volume(float v){
  AudioUtils::volume=v;
}
void AudioUtils::set_music_volume(float v){
  AudioUtils::music_volume=v;
}

void AudioUtils::set_subtitling_renderer(TextRenderer* text_renderer){
  subtitle_settings->text_renderer=text_renderer;
}

void AudioUtils::set_subtitling(bool subtitle, Weight::RenderEngine::Font* font, Weight::Colour colour, float font_size){
  subtitle_settings->subtitle=subtitle;
  subtitle_settings->font=font;
  subtitle_settings->colour=colour;
  subtitle_settings->font_size=font_size;
}
AudioUtils::SubtitlingSettings* AudioUtils::get_subtitling_settings(){
  return AudioUtils::subtitle_settings;
}

unsigned int AudioUtils::load_sound(std::string file){
  unsigned int buffer;
  alGenBuffers(1, &buffer);

  ALsizei size, frequency;
  ALenum format;
  ALvoid* data;
  char* path=(char*)file.c_str();
  alutLoadWAVFile(path, &format, &data, &size, &frequency);
  alBufferData(buffer, format, data, size, frequency);
  return buffer;
}

void AudioUtils::set_distance_model(int model){
  alDistanceModel(model);
}
