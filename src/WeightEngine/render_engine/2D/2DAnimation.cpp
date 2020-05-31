#include <WeightEngine/render_engine/2D/2DAnimation.h>

using namespace Weight;
using namespace RenderEngine;

Animation2D::Animation2D(std::string texture_path, std::string details_path){
  animation_data=json::parse(Utils::load_file(details_path));
  if(!animation_data["tiling_information"]){
    WEIGHT_ERROR("Animation2D: Error loading animations: {0}. Please specify the information for the sprite width and height in JSON file with attribute key tiling_information", texture_path);
    this->Animation2D::~Animation2D();
    return;
  }
  texture_atlas=new TextureAtlas(texture_path, animation_data["tiling_information"][0], animation_data["tiling_information"][1]);
}
Animation2D::~Animation2D(){
  this->texture_atlas->~TextureAtlas();
}

void Animation2D::reload_animations(std::string texture_path, std::string details_path){
  animation_data=json::parse(Utils::load_file(details_path));
  if(!animation_data["tiling_information"]){
    WEIGHT_ERROR("Animation2D: Error loading animations: {0}. Please specify the information for the sprite width and height in JSON file with attribute key tiling_information", texture_path);
    this->Animation2D::~Animation2D();
    return;
  }
  texture_atlas->reload_texture(texture_path, animation_data["tiling_information"][0], animation_data["tiling_information"][1]);
}
void Animation2D::play_animation(std::string name, int frame_start, bool _loop){
  play=true;
  loop=_loop;
  frame_number=frame_start;
  frame_count=animation_data[name][1];
  start_tile=animation_data[name][0];
  current_animation=name;

  float duration=animation_data[name][2];
  frame_step=duration/frame_count;
}
void Animation2D::stop_animation(){
  play=false;
}

SubTexture* Animation2D::update(){
  if(play){
    time_accumulation+=Time::get()->get_time_step();
    if(time_accumulation>=frame_step){
      if(frame_number>=frame_count&&loop){
        frame_number=0;
      }else{
        play=false;
      }
      frame_number++;
      time_accumulation=0.0f;
    }
  }
  int frame_index=start_tile+frame_number;
  return texture_atlas->get_texture(texture_atlas->text_width*(frame_index%texture_atlas->textures_wide),
                                  texture_atlas->image_height-(texture_atlas->text_height*(frame_index%texture_atlas->textures_wide)));
}
