#include <WeightEngine/render_engine/2D/2DLightSystem.h>

using namespace Weight;
using namespace RenderEngine;

LightSystem2D::LightSystem2D(unsigned int _max_lights):max_lights(_max_lights), max_vertex(_max_lights*4), max_index(_max_lights*6){
  lights.reserve(max_lights);

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
}
LightSystem2D::~LightSystem2D(){
  glDeleteVertexArrays(1, &vertex_array);
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteBuffers(1, &index_buffer);
}

Light2D* LightSystem2D::create_light(Position2D position, Colour colour, float size, bool affect_mvp){
  return new Light2D(position, colour, size, affect_mvp);
}

void LightSystem2D::render(glm::mat4 mvp, float ts){
  std::vector<Vertex> vertices;
  vertices.reserve(lights.size()*4);
  for(int i=0; i<lights.size(); i++){
    for(int j=0; j<4; j++){
      vertices.push_back(lights[i]->vertices[j]);
    }
  }
  glBindVertexArray(vertex_array);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(Vertex), vertices.data());
  Light2DShader::get()->bind();
  Light2DShader::get()->set_matrix("mvp", mvp);
  glDrawElements(GL_TRIANGLES, 6*vertices.size()*0.25, GL_UNSIGNED_INT, nullptr);
  vertices.clear();
}
void LightSystem2D::submit(Light2D* l){
  if(lights.size()>=max_lights){
    WEIGHT_WARNING("Lights2D: Max number of lights reached");
    return;
  }else{
    lights.push_back(l);
  }
}
void LightSystem2D::remove(Light2D* l){
  lights.erase(std::find(lights.begin(), lights.end(), l));
}
