#include <WeightEngine/render_engine/gui/button.h>

using namespace WeightEngine;
using namespace RenderEngine;
using namespace GUI;

Button::Button(Label* _label, Position2D _pos, float _width, float _height, Colour _default_colour, Colour _pressed_colour, std::function<void()> _callback):Widget(Random::get_float()){
  label_instance=_label;
  pos=_pos;
  width=_width;
  height=_height;
  default_colour=_default_colour;
  pressed_colour=_pressed_colour;
  callback=_callback;
}
Button::~Button(){
  Renderer_2D->remove(quad_instance);
  text_renderer->remove(label_instance->instance);
}

void Button::set_label(Label* _label){
  label_instance=_label;
}
void Button::set_position(Position2D _pos){
  quad_instance->set_position(pos);
  Position2D bounds[4]={
    {quad_instance->vertices[0].position.x, quad_instance->vertices[0].position.y},
    {quad_instance->vertices[1].position.x, quad_instance->vertices[1].position.y},
    {quad_instance->vertices[2].position.x, quad_instance->vertices[2].position.y},
    {quad_instance->vertices[3].position.x, quad_instance->vertices[3].position.y},
  };
  update_bounds(bounds);
}
void Button::set_size(float _width, float _height){
  quad_instance->set_size(_width, _height);
  Position2D bounds[4]={
    {quad_instance->vertices[0].position.x, quad_instance->vertices[0].position.y},
    {quad_instance->vertices[1].position.x, quad_instance->vertices[1].position.y},
    {quad_instance->vertices[2].position.x, quad_instance->vertices[2].position.y},
    {quad_instance->vertices[3].position.x, quad_instance->vertices[3].position.y},
  };
  update_bounds(bounds);
}
void Button::set_default_colour(Colour _default_colour){
  default_colour=_default_colour;
}
void Button::set_pressed_colour(Colour _pressed_colour){
  pressed_colour=_pressed_colour;
}
void Button::set_callback(std::function<void()> _callback){
  callback=_callback;
}

void Button::on_mouse_press(MousePressEvent* e){
  callback();
}

void Button::on_setup(){
  quad_instance=Renderer_2D->create_quad(pos, width, height, default_colour, false);
  Renderer_2D->submit(quad_instance);
}

void Button::on_lose_focus(){
  quad_instance->fill(default_colour);
}
void Button::on_gain_focus(){
  quad_instance->fill(pressed_colour);
}
