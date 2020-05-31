#include <WeightEngine/render_engine/2D/2DLight.h>

using namespace Weight;
using namespace RenderEngine;

Light2D::Light2D(Position2D _position, Colour _colour, float _size, bool _affect_mvp){
  position=_position;
  colour=_colour;
  size=_size;
  affect_mvp=_affect_mvp;
  vertices[0]={{(float)(position.x-size*0.5), (float)(position.y-size*0.5), 0.0f}, colour, {-1.0f, -1.0f}, 0.0f, (affect_mvp)?1.0f:0.0f};
  vertices[1]={{(float)(position.x+size*0.5), (float)(position.y-size*0.5), 0.0f}, colour, {1.0f, -1.0f}, 0.0f, (affect_mvp)?1.0f:0.0f};
  vertices[2]={{(float)(position.x+size*0.5), (float)(position.y+size*0.5), 0.0f}, colour, {1.0f, 1.0f}, 0.0f, (affect_mvp)?1.0f:0.0f};
  vertices[3]={{(float)(position.x-size*0.5), (float)(position.y+size*0.5), 0.0f}, colour, {-1.0f, 1.0f}, 0.0f, (affect_mvp)?1.0f:0.0f};
}
Light2D::~Light2D(){

}

void Light2D::set_position(Position2D pos){
  position=pos;
  vertices[0].position={(float)(pos.x-size*0.5), (float)(pos.y-size*0.5), 0.0f};
  vertices[1].position={(float)(pos.x+size*0.5), (float)(pos.y-size*0.5), 0.0f};
  vertices[2].position={(float)(pos.x+size*0.5), (float)(pos.y+size*0.5), 0.0f};
  vertices[3].position={(float)(pos.x-size*0.5), (float)(pos.y+size*0.5), 0.0f};
}
void Light2D::move(Vector2D translation){
  for(int i=0; i<4; i++){
    vertices[i].position.x+=translation.x;
    vertices[i].position.y+=translation.y;
  }
}
void Light2D::set_colour(Colour _colour){
  colour=_colour;
  for(int i=0; i<4; i++){
    vertices[i].colour=_colour;
  }
}
void Light2D::set_size(float _size){
  size=_size;
  set_position(position);
}

Position2D Light2D::get_position(){
  return position;
}
Colour Light2D::get_colour(){
  return colour;
}
float Light2D::get_size(){
  return size;
}
