#include <WeightEngine/audio/music_manager.h>

using namespace Weight;
using namespace Audio;


MusicManager::MusicManager(){
  source=new Source(true);
  source->loop();
}
MusicManager::~MusicManager(){
  this->source->~Source();
}

void MusicManager::load_music(std::string path, std::string shortcut_name){
  music[shortcut_name]=AudioUtils::load_sound(path);
  load_music(shortcut_name);
}
void MusicManager::load_music(std::string shortcut_name){
  source->setup(music[shortcut_name], 0, 1, 2);
}

//We assume that music loops
void MusicManager::play(){
  source->set_volume(AudioUtils::get_music_volume());
  source->play();
}
void MusicManager::pause(){
  source->pause();
}
void MusicManager::stop(){
  source->stop();
}

/*
void MusicManager::set_volume(float vol){
  source->set_volume(vol);
}*/

void MusicManager::set_pitch(float pitch){
  source->set_pitch(pitch);
}
