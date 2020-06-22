#include <WeightEngine/render_engine/gui/image.h>

using namespace WeightEngine;
using namespace RenderEngine;
using namespace GUI;

Image::Image(std::string _path, Position2D _pos, float _width, float _height):Widget(Random::get_float()){
  path=_path;
  pos=_pos;
  width=_width;
  height=_height;
}
Image::~Image(){
  Renderer_2D->remove(instance);
}

void Image::set_texture(std::string _path){
  instance->set_texture(_path);
}
void Image::set_size(float _width, float _height){
  instance->set_size(_width, _height);
  Position2D bounds[4]={
    {instance->vertices[0].position.x, instance->vertices[0].position.y},
    {instance->vertices[1].position.x, instance->vertices[1].position.y},
    {instance->vertices[2].position.x, instance->vertices[2].position.y},
    {instance->vertices[3].position.x, instance->vertices[3].position.y},
  };
  update_bounds(bounds);
}
void Image::set_position(Position2D _pos){
  instance->set_position(_pos);
  Position2D bounds[4]={
    {instance->vertices[0].position.x, instance->vertices[0].position.y},
    {instance->vertices[1].position.x, instance->vertices[1].position.y},
    {instance->vertices[2].position.x, instance->vertices[2].position.y},
    {instance->vertices[3].position.x, instance->vertices[3].position.y},
  };
  update_bounds(bounds);
}

void Image::on_setup(){
  Renderer_2D->create_quad(pos, width, height, path, false);
  Renderer_2D->submit(instance);
}
