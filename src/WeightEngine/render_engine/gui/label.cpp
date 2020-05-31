#include <WeightEngine/render_engine/gui/label.h>

using namespace Weight;
using namespace RenderEngine;
using namespace GUI;


Label::Label(std::string _text, Position2D _pos, Font* _font, Colour _colour, float _size):Widget(Random::get_float()){
  text=_text;
  pos=_pos;
  font=_font;
  colour=_colour;
  size=_size;
}
Label::~Label(){
  text_renderer->remove(instance);
}

void Label::set_position(Position2D _pos){
  instance->set_position(_pos);
  Position2D bounds[4]={
    {instance->character_data[0].vertices[0].position.x, instance->character_data[0].vertices[0].position.y},
    {instance->character_data[instance->character_data.size()].vertices[1].position.x, instance->character_data[instance->character_data.size()].vertices[1].position.y},
    {instance->character_data[instance->character_data.size()].vertices[2].position.x, instance->character_data[instance->character_data.size()].vertices[2].position.y},
    {instance->character_data[0].vertices[3].position.x, instance->character_data[0].vertices[3].position.y},
  };
  update_bounds(bounds);
}
void Label::set_colour(Colour _colour){
  instance->set_colour(_colour);
}
void Label::set_size(float _size){
  instance->set_size(_size);
  Position2D bounds[4]={
    {instance->character_data[0].vertices[0].position.x, instance->character_data[0].vertices[0].position.y},
    {instance->character_data[instance->character_data.size()].vertices[1].position.x, instance->character_data[instance->character_data.size()].vertices[1].position.y},
    {instance->character_data[instance->character_data.size()].vertices[2].position.x, instance->character_data[instance->character_data.size()].vertices[2].position.y},
    {instance->character_data[0].vertices[3].position.x, instance->character_data[0].vertices[3].position.y},
  };
  update_bounds(bounds);
}
void Label::rotate(float _degrees){
  instance->rotate(_degrees);
}

void Label::on_setup(){
  instance=text_renderer->generate_text(text, pos, font, colour, size, false);
  text_renderer->submit(instance);
}
