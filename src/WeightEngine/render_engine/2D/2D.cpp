#include <WeightEngine/render_engine/2D/2D.h>

using namespace WeightEngine;
using namespace RenderEngine;

void QuadData::move(Position3D translation){
  for(int i=0; i<4; i++){
    this->vertices[i].position.x+=translation.x;
    this->vertices[i].position.y+=translation.y;
    this->vertices[i].position.z+=translation.z;
  }
}
void QuadData::move(Position2D translation){
  Position3D arg={translation.x, translation.y, 0};
  move(arg);
}

void QuadData::set_position(Position3D position){
  this->vertices[0].position={position.x, position.y, position.z};
  this->vertices[1].position={position.x+dimensions.x, position.y, position.z};
  this->vertices[2].position={position.x+dimensions.x, position.y+dimensions.y, position.z};
  this->vertices[3].position={position.x, position.y+dimensions.y, position.z};
}
void QuadData::set_position(Position2D position){
  Position3D arg={position.x, position.y, 0.0f};
  set_position(arg);
}
void QuadData::set_size(float width, float height){
  dimensions={width, height};
  set_position(this->vertices[0].position);
}

void QuadData::rotate(float degrees){
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
void QuadData::flip(int axis){
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
void QuadData::scale(float factor){
  float current_width=this->vertices[1].position.x-this->vertices[0].position.x;
  float current_height=this->vertices[2].position.y-this->vertices[0].position.y;
  this->vertices[1].position.x=this->vertices[0].position.x+(current_width*factor);
  this->vertices[2].position.x=this->vertices[0].position.x+(current_width*factor);
  this->vertices[2].position.y=this->vertices[0].position.y+(current_height*factor);
  this->vertices[3].position.y=this->vertices[0].position.y+(current_height*factor);
}

void QuadData::set_texture(std::string path){
  this->texture_id=Utils::load_opengl_texture(Utils::load_image(path));
}

void QuadData::set_texture_from_atlas(SubTexture* texture){
  texture_id=texture->texture_id;
  for(int i=0; i<8; i+=2){
    vertices[i/2].texture_coords.x=texture->texture_coords[i];
    vertices[i/2].texture_coords.y=texture->texture_coords[i+1];
  }
}

void QuadData::fill(Colour colour){
  for(int i=0; i<4; i++){
    this->vertices[i].colour=colour;
  }
}


Renderer2D::Renderer2D(int _max_quad):max_quad(_max_quad), max_vertex(_max_quad*4), max_index(_max_quad*6), id_number(0){
  geometry.reserve(max_quad);
  for(int i=0; i<MAX_TEXTURES; i++){
    samplers[i]=i;
  }

  //Setup blank texture for quads that just want a colour
  blank_texture_id=Utils::load_blank_opengl_texture();

  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*max_vertex, nullptr, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, colour));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texture_coords));

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texture_slot));

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, affect_mvp));

  unsigned int indices[max_index];
  unsigned int offset=0;
  for(size_t i=0; i<max_index; i+=6){
    indices[i+0]=0+offset;
    indices[i+1]=1+offset;
    indices[i+2]=2+offset;
    indices[i+3]=2+offset;
    indices[i+4]=3+offset;
    indices[i+5]=0+offset;
    offset+=4;
  }

  glGenBuffers(1, &index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  WEIGHT_SUCCESS("2D Renderer initialised");
}
Renderer2D::~Renderer2D(){
  glDeleteVertexArrays(1, &vertex_array);
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteBuffers(1, &index_buffer);
}

QuadData* Renderer2D::create_quad(Position2D position, float width, float height, Colour colour, bool affect_mvp){
  return create_quad({position.x, position.y, 0.0f}, width, height, colour);
}
QuadData* Renderer2D::create_quad(Position2D position, float width, float height, std::string texture_path, bool affect_mvp){
  return create_quad({position.x, position.y, 0.0f}, width, height, texture_path);
}

QuadData* Renderer2D::create_quad(Position3D position, float width, float height, Colour colour, bool affect_mvp){
  QuadData* result=new QuadData;
  result->id=id_number++;
  result->texture_id=blank_texture_id;

  result->dimensions={width, height};

  //Drawing so that the position of the quad given is the bottom left of the quad
  result->vertices[0].position={position.x, position.y, position.z};
  result->vertices[0].colour=colour;
  result->vertices[0].texture_coords={0.0f, 0.0f};
  result->vertices[0].texture_slot=0.0f;
  result->vertices[0].affect_mvp=affect_mvp?1.0f:0.0f;

  result->vertices[1].position={position.x+width, position.y, position.z};
  result->vertices[1].colour=colour;
  result->vertices[1].texture_coords={0.0f, 0.0f};
  result->vertices[1].texture_slot=0.0f;
  result->vertices[1].affect_mvp=affect_mvp?1.0f:0.0f;

  result->vertices[2].position={position.x+width, position.y+height, position.z};
  result->vertices[2].colour=colour;
  result->vertices[2].texture_coords={0.0f, 0.0f};
  result->vertices[2].texture_slot=0.0f;
  result->vertices[2].affect_mvp=affect_mvp?1.0f:0.0f;

  result->vertices[3].position={position.x, position.y+height, position.z};
  result->vertices[3].colour=colour;
  result->vertices[3].texture_coords={0.0f, 0.0f};
  result->vertices[3].texture_slot=0.0f;
  result->vertices[3].affect_mvp=affect_mvp?1.0f:0.0f;

  return result;
}

QuadData* Renderer2D::create_quad(Position3D position, float width, float height, std::string texture_path, bool affect_mvp){
  QuadData* result=new QuadData;
  result->id=id_number++;
  result->texture_id=Utils::load_opengl_texture(Utils::load_image(texture_path));

  result->dimensions={width, height};

  //Drawing so that the position of the quad given is the bottom left of the quad
  result->vertices[0].position={position.x, position.y, position.z};
  result->vertices[0].colour={0.0f, 0.0f, 0.0f, 0.0f};
  result->vertices[0].texture_coords={0.0f, 0.0f};
  result->vertices[0].texture_slot=0.0f;
  result->vertices[0].affect_mvp=affect_mvp?1.0f:0.0f;

  result->vertices[1].position={position.x+width, position.y, position.z};
  result->vertices[1].colour={0.0f, 0.0f, 0.0f, 0.0f};
  result->vertices[1].texture_coords={1.0f, 0.0f};
  result->vertices[1].texture_slot=0.0f;
  result->vertices[1].affect_mvp=affect_mvp?1.0f:0.0f;

  result->vertices[2].position={position.x+width, position.y+height, position.z};
  result->vertices[2].colour={0.0f, 0.0f, 0.0f, 0.0f};
  result->vertices[2].texture_coords={1.0f, 1.0f};
  result->vertices[2].texture_slot=0.0f;
  result->vertices[2].affect_mvp=affect_mvp?1.0f:0.0f;

  result->vertices[3].position={position.x, position.y+height, position.z};
  result->vertices[3].colour={0.0f, 0.0f, 0.0f, 0.0f};
  result->vertices[3].texture_coords={0.0f, 1.0f};
  result->vertices[3].texture_slot=0.0f;
  result->vertices[3].affect_mvp=affect_mvp?1.0f:0.0f;

  return result;
}

void Renderer2D::submit(QuadData* q){
  if(geometry.size()>=max_quad){
    WEIGHT_WARNING("2D: Max number of quads met. Cannot render quad id: {0}", q->id);
    return;
  }else{
    geometry.push_back(q);
  }
}

void Renderer2D::remove(QuadData* q){
  geometry.erase(std::find(geometry.begin(), geometry.end(), q));
}

void Renderer2D::render(glm::mat4 mvp, float ts){
  glBindVertexArray(vertex_array);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  BasicShader::get()->bind();
  BasicShader::get()->set_int_array("textures", samplers, MAX_TEXTURES);

  std::vector<Vertex> vertices;
  std::vector<unsigned int> texture_ids;
  std::vector<unsigned int>::iterator id_location;
  unsigned int number_textures=1;
  unsigned int opengl_texture_id=1;

  vertices.reserve(ceil(geometry.size()*0.3)*4);
  texture_ids.push_back(blank_texture_id);
  //glBindTextureUnit(0, blank_texture_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, blank_texture_id);

  for(int i=0; i<geometry.size(); i++){
    if(geometry[i]->texture_id==blank_texture_id){
      opengl_texture_id=0;
    }else{
      id_location=std::find(texture_ids.begin(), texture_ids.end(), geometry[i]->texture_id);
      if(id_location==texture_ids.end()){
        texture_ids.push_back(geometry[i]->texture_id);
        opengl_texture_id=number_textures++;
        //glBindTextureUnit(opengl_texture_id, geometry[i]->texture_id);
        glActiveTexture(GL_TEXTURE0+opengl_texture_id);
        glBindTexture(GL_TEXTURE_2D, geometry[i]->texture_id);
      }else{
        opengl_texture_id=*id_location;
      }
    }

    for(int j=0; j<4; j++){
      geometry[i]->vertices[j].texture_slot=opengl_texture_id;
      vertices.push_back(geometry[i]->vertices[j]);
    }
    if(number_textures+1==MAX_TEXTURES||i+1==geometry.size()){
      glBindVertexArray(vertex_array);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
      glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(Vertex), vertices.data());
      BasicShader::get()->set_matrix("mvp", mvp);

      glDrawElements(GL_TRIANGLES, 6*vertices.size()*0.25, GL_UNSIGNED_INT, nullptr);

      vertices.clear();
      texture_ids.clear();
      number_textures=1;
    }
  }
}

void Renderer2D::set_background_image(std::string background_path){
  if(background_path!=""){
    geometry.insert(geometry.begin(), create_quad({-1.0f, 1.0f, -1.0f}, 1.0f, 1.0f, background_path, false));
  }else{
    if(geometry[0]->vertices[0].position==Utils::create_position(-1.0f, 1.0f, -1.0f)&&geometry[0]->vertices[3].position==Utils::create_position(1.0f, -1.0f, -1.0f)){
      geometry.erase(geometry.begin());
    }
  }
}

void Renderer2D::render_background(glm::mat4 mvp){
  if(geometry[0]->vertices[0].position==Utils::create_position(-1.0f, 1.0f, -1.0f)&&geometry[0]->vertices[3].position==Utils::create_position(1.0f, -1.0f, -1.0f)){
    glActiveTexture(GL_TEXTURE0+1);
    glBindTexture(GL_TEXTURE_2D, geometry[0]->texture_id);
    for(int i=0; i<4; i++){
      geometry[0]->vertices[i].texture_slot=1.0f;
    }
    glBindVertexArray(vertex_array);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4*sizeof(Vertex), geometry[0]->vertices);
    BasicShader::get()->bind();
    BasicShader::get()->set_matrix("mvp", mvp);
    glDrawElements(GL_TRIANGLES, 6*4*0.25, GL_UNSIGNED_INT, nullptr);
  }
}
