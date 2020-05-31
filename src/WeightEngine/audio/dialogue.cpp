#include <WeightEngine/audio/dialogue.h>

using namespace Weight;
using namespace Audio;
using json=nlohmann::json;

Dialogue::Dialogue():Source(){
  subtitle_settings=AudioUtils::get_subtitling_settings();
}
Dialogue::~Dialogue(){

}

/*
JSON file set out like this:
{
  "0":["0:00", "Hello there", "0:02"],
  "1":["0:04", "General Kenobi", "0:06"],
  ...
}
 */
void Dialogue::load_dialogue(std::string path, std::string transcript_path){
  setup(AudioUtils::load_sound(path));
  dialogue_segments.empty();
  json object=json::parse(Utils::load_file(transcript_path));
  for(json::iterator it=object.begin(); it!=object.end(); it++){
    dialogue_segments.push_back({Utils::timestamp_to_number(it.value()[0]), it.value()[1], Utils::timestamp_to_number(it.value()[2])});
  }
  WEIGHT_SUCCESS("Dialogue: Loaded {0}", path);
}

void Dialogue::play(std::string dialogue){
  int index=-1;
  for(int i=0; i<dialogue_segments.size(); i++){
    if(dialogue_segments[i].transcript==dialogue){
      index=i;
      break;
    }
  }
  play(index);
}
void Dialogue::play(int index){
  if(index>dialogue_segments.size()||index<0){
    WEIGHT_WARNING("Dialogue: No valid index for value given");
    return;
  }
  set_playback_pointer(dialogue_segments[index].start_time);
  set_volume(dialogue_segments[index].volume);
  std::thread subtitle_thread(Dialogue::subtitle, AudioUtils::subtitle_settings, dialogue_segments[index].transcript);
  std::thread count_thread(Dialogue::count, get_source_id(), dialogue_segments[index].end_time-dialogue_segments[index].start_time);
  this->Source::play();
  subtitle_thread.join();
  count_thread.join();
}

void Dialogue::count(int id, float duration){
  std::this_thread::sleep_for(std::chrono::seconds(static_cast<long long>(duration)));
  alSourcePause(id);
}

void Dialogue::subtitle(AudioUtils::SubtitlingSettings* settings, std::string transcript){
  if(settings->subtitle){
    Position2D pos={-0.9f, -0.9f};
    settings->text_renderer->generate_text(transcript, pos, settings->font, settings->colour, settings->font_size, false);
  }
}
