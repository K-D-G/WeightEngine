#include <WeightEngine/render_engine/2D/2DAnimation.h>

using namespace WeightEngine;
using namespace RenderEngine;

Animation2D::Animation2D(std::string texture_path, std::string details_path){
  animation_data=json::parse(Utils::load_file(details_path));
  if(animation_data.find("frames")==animation_data.end()){
    WEIGHT_ERROR("Animation2D: Error loading animations: {0}. JSON file doesn't contain frame data for subtexturing", texture_path);
    this->Animation2D::~Animation2D();
    return;
  }
  width=animation_data["meta"]["size"]["w"];
  height=animation_data["meta"]["size"]["h"];
  animation_data=animation_data["frames"];
  texture_id=Utils::load_opengl_texture(Utils::load_image(texture_path));
  frame=new SubTexture;
  //texture_atlas=new TextureAtlas(texture_path, (animation_data.begin())["sourceSize"]["w"], (animation_data.begin())["sourceSize"]["h"]);
}
Animation2D::~Animation2D(){
  //this->texture_atlas->~TextureAtlas();
}

void Animation2D::reload_animations(std::string texture_path, std::string details_path){
  animation_data=json::parse(Utils::load_file(details_path));
  if(animation_data.find("frames")==animation_data.end()){
    WEIGHT_ERROR("Animation2D: Error loading animations: {0}. JSON file doesn't contain frame data for subtexturing", texture_path);
    return;
  }
  width=animation_data["meta"]["size"]["w"];
  height=animation_data["meta"]["size"]["h"];
  animation_data=animation_data["frames"];
  //texture_atlas->reload_texture(texture_path, (animation_data.begin())["sourceSize"]["w"], (animation_data.begin())["sourceSize"]["h"]);
  texture_id=Utils::load_opengl_texture(Utils::load_image(texture_path));
}
void Animation2D::play_animation(std::string _name, int frame_start, bool _loop){
  play=true;
  loop=_loop;
  name=_name;
  frame_number=frame_start;

  frame_count=0;
  for(auto it=animation_data.begin(); it!=animation_data.end(); ++it){
    if(animation_data.find((name+" "+std::to_string(frame_count+1)+".").c_str())!=animation_data.end()){
      frame_count++;
    }
  }

  current_animation=name;
  frame_name=(char*)((name+" "+std::to_string(frame_start)+".").c_str());
  frame_step=static_cast<int>(animation_data[frame_name]["duration"])*0.001f;
}
void Animation2D::stop_animation(){
  play=false;
}

SubTexture* Animation2D::update(){
  if(play){
    time_accumulation+=Time::get()->get_time_step();
    if(time_accumulation>=frame_step){
      frame_number++;
      if(frame_number>frame_count&&loop){
        frame_number=0;
      }else if(frame_number>frame_count){
        play=false;
      }
      frame_name=(name+" "+std::to_string(frame_number)+".");
      frame_step=static_cast<int>(animation_data[frame_name]["duration"])*0.001f;
      time_accumulation=0.0f;
    }
  }
  frame->texture_id=texture_id;

  int x=animation_data[frame_name]["frame"]["x"];
  int y=animation_data[frame_name]["frame"]["y"];
  int w=animation_data[frame_name]["frame"]["w"];
  int h=animation_data[frame_name]["frame"]["h"];
  frame->texture_coords[0]=Maths::map(x, 0, width, 0, 1, false);
  frame->texture_coords[1]=Maths::map(y, 0, height, 0, 1, false);

  frame->texture_coords[2]=Maths::map(x+w, 0, width, 0, 1, false);
  frame->texture_coords[3]=Maths::map(y, 0, height, 0, 1, false);

  frame->texture_coords[4]=Maths::map(x+w, 0, width, 0, 1, false);
  frame->texture_coords[5]=Maths::map(y+h, 0, height, 0, 1, false);

  frame->texture_coords[6]=Maths::map(x, 0, width, 0, 1, false);
  frame->texture_coords[7]=Maths::map(y+h, 0, height, 0, 1, false);

  frame->x=0;
  frame->y=0;

  return frame;
}
