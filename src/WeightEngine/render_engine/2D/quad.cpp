#include <WeightEngine/render_engine/2D/quad.h>

using namespace WeightEngine;
using namespace RenderEngine;

void Quad::move(Position3D translation){
  for(int i=0; i<4; i++){
    this->vertices[i].position.x+=translation.x;
    this->vertices[i].position.y+=translation.y;
    this->vertices[i].position.z+=translation.z;
  }
}
void Quad::move(Position2D translation){
  Position3D arg={translation.x, translation.y, 0};
  move(arg);
}

void Quad::set_position(Position3D position){
  this->vertices[0].position={position.x, position.y, position.z};
  this->vertices[1].position={position.x+dimensions.x, position.y, position.z};
  this->vertices[2].position={position.x+dimensions.x, position.y+dimensions.y, position.z};
  this->vertices[3].position={position.x, position.y+dimensions.y, position.z};
}
void Quad::set_position(Position2D position){
  Position3D arg={position.x, position.y, 0.0f};
  set_position(arg);
}
void Quad::set_size(float width, float height){
  dimensions={width, height};
  set_position(this->vertices[0].position);
}

void Quad::rotate(float degrees){
  float radians=glm::radians(degrees);

  float dimensions[2]={this->vertices[2].position.x-this->vertices[0].position.x, this->vertices[2].position.y-this->vertices[0].position.y};
  float centre[2]={static_cast<float>(this->vertices[0].position.x+dimensions[0]*0.5), static_cast<float>(this->vertices[0].position.y+dimensions[1]*0.5)};

  float oldx, oldy;
  for(int i=0; i<4; i++){
    oldx=this->vertices[i].position.x-centre[0];
    oldy=this->vertices[i].position.y-centre[1];
    this->vertices[i].position.x=oldx*cos(radians)-oldy*sin(radians);
    this->vertices[i].position.y=oldx*sin(radians)+oldy*cos(radians);

    this->vertices[i].position.x+=centre[0];
    this->vertices[i].position.y+=centre[1];
  }
}
void Quad::flip(int axis){
  if(axis==X_AXIS){
    //Swap the x0 y0 and x1 y1 (and the other 2)
    Vertex buffer=this->vertices[0];
    this->vertices[0]=this->vertices[1];
    this->vertices[1]=buffer;

    buffer=this->vertices[2];
    this->vertices[2]=this->vertices[3];
    this->vertices[3]=buffer;
  }else if(axis==Y_AXIS){
    //Swap the x0 y0 and x3 y3 (and the other 2)
    Vertex buffer=this->vertices[0];
    this->vertices[0]=this->vertices[3];
    this->vertices[3]=buffer;

    buffer=this->vertices[1];
    this->vertices[1]=this->vertices[2];
    this->vertices[2]=buffer;
  }
}
void Quad::scale(float factor){
  float current_width=this->vertices[1].position.x-this->vertices[0].position.x;
  float current_height=this->vertices[2].position.y-this->vertices[0].position.y;
  this->vertices[1].position.x=this->vertices[0].position.x+(current_width*factor);
  this->vertices[2].position.x=this->vertices[0].position.x+(current_width*factor);
  this->vertices[2].position.y=this->vertices[0].position.y+(current_height*factor);
  this->vertices[3].position.y=this->vertices[0].position.y+(current_height*factor);
}

void Quad::set_texture(std::string path){
  this->texture_id=Utils::load_opengl_texture(Utils::load_image(path));
}

void Quad::set_texture_from_atlas(SubTexture* texture){
  texture_id=texture->texture_id;
  for(int i=0; i<8; i+=2){
    vertices[i/2].texture_coords.x=texture->texture_coords[i];
    vertices[i/2].texture_coords.y=texture->texture_coords[i+1];
  }
}

void Quad::fill(Colour colour){
  for(int i=0; i<4; i++){
    this->vertices[i].colour=colour;
  }
}
