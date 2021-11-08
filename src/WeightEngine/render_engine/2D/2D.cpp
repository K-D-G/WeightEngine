#include <WeightEngine/render_engine/2D/2D.h>

using namespace WeightEngine;
using namespace RenderEngine;

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

Quad* Renderer2D::create_quad(Position2D position, float width, float height, Colour colour, bool affect_mvp){
  return create_quad({position.x, position.y, 0.0f}, width, height, colour);
}
Quad* Renderer2D::create_quad(Position2D position, float width, float height, std::string texture_path, bool affect_mvp){
  return create_quad({position.x, position.y, 0.0f}, width, height, texture_path);
}

Quad* Renderer2D::create_quad(Position3D position, float width, float height, Colour colour, bool affect_mvp){
  Quad* result=new Quad;
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

Quad* Renderer2D::create_quad(Position3D position, float width, float height, std::string texture_path, bool affect_mvp){
  Quad* result=new Quad;
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

void Renderer2D::submit(Quad* q){
  if(geometry.size()>=max_quad){
    WEIGHT_WARNING("2D: Max number of quads met. Cannot render quad id: {0}", q->id);
    return;
  }else{
    geometry.push_back(q);
  }
}

void Renderer2D::remove(Quad* q){
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
