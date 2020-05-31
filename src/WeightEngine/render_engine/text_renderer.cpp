#include <WeightEngine/render_engine/text_renderer.h>

using namespace Weight;
using namespace RenderEngine;

void Text::move(Position3D translation){
  for(int i=0; i<character_data.size(); i++){
    for(int j=0; j<4; j++){
      character_data[i].vertices[j].position.x+=translation.x;
      character_data[i].vertices[j].position.y+=translation.y;
      character_data[i].vertices[j].position.z+=translation.z;
    }
  }
}
void Text::move(Position2D translation){
  move({translation.x, translation.y, 0.0f});
}
void Text::set_position(Position3D position){
  pos=position;
  character_data.empty();
  character_data.reserve(text.length());

  Vector2D atlas_dimensions=font->get_atlas_dimensions();
  float x, y, x2, y2, w, h;
  x=pos.x;
  y=pos.y;
  for(int i=0; i<text.length(); i++){
    x2=x+font->characters[text[i]].bearing.x*size;
    y2=-y-font->characters[text[i]].bearing.y*size;
    w=font->characters[text[i]].size.x*size;
    h=font->characters[text[i]].size.y*size;

    x+=font->characters[text[i]].advance.x*size;
    y+=font->characters[text[i]].advance.y*size;

    if(!w||!h){
      continue;
    }

    CharacterRenderData c;
    c.vertices[0].position={x2, -y2, position.z};
    c.vertices[0].texture_coords={font->characters[text[i]].offset, 0};

    c.vertices[1].position={x2+w, -y2, position.z};
    c.vertices[1].texture_coords={font->characters[text[i]].offset+font->characters[text[i]].size.x/atlas_dimensions.x, 0};

    c.vertices[2].position={x2, -y2-h, position.z};
    c.vertices[2].texture_coords={font->characters[text[i]].offset, font->characters[text[i]].size.y/atlas_dimensions.y};

    c.vertices[3].position={x2+w, -y2-h, position.z};
    c.vertices[3].texture_coords={font->characters[text[i]].offset+font->characters[text[i]].size.x/atlas_dimensions.x, font->characters[text[i]].size.y/atlas_dimensions.y};
    character_data.push_back(c);
  }
}
void Text::set_position(Position2D position){
  set_position({position.x, position.y, 0.0f});
}
void Text::set_colour(Colour _colour){
  colour=_colour;
}

void Text::set_size(float _size){
  size=_size;
}
int Text::get_size(){
  return size;
}

void Text::rotate(float degrees){
  Position2D centre={
    (float)((character_data[0].vertices[0].position.x+character_data[character_data.size()-1].vertices[2].position.x)*0.5),
    (float)((character_data[0].vertices[0].position.y+character_data[character_data.size()-1].vertices[2].position.y)*0.5)
  };
  float radians=glm::radians(degrees);
  float oldx, oldy;
  for(int i=0; i<character_data.size(); i++){
    for(int j=0; j<4; j++){
      oldx=character_data[i].vertices[j].position.x-centre.x;
      oldy=character_data[i].vertices[j].position.y-centre.y;

      character_data[i].vertices[j].position.x=oldx*cos(radians)-oldy*sin(radians);
      character_data[i].vertices[j].position.y=oldx*sin(radians)+oldy*cos(radians);

      character_data[i].vertices[j].position.x+=centre.x;
      character_data[i].vertices[j].position.y+=centre.y;
    }
  }
}
/*
void Text::scale(float factor){
  for(int i=0; i<character_data.size(); i++){
    float current_width=this->character_data[i]->vertices[1].position.x-this->character_data[i]->vertices[0].position.x;
    float current_height=this->character_data[i]->vertices[2].position.y-this->character_data[i]->vertices[0].position.y;
    this->character_data[i]->vertices[1].position.x=this->character_data[i]->vertices[0].position.x+(current_width*factor);
    this->character_data[i]->vertices[2].position.x=this->character_data[i]->vertices[0].position.x+(current_width*factor);
    this->character_data[i]->vertices[2].position.y=this->character_data[i]->vertices[0].position.y+(current_height*factor);
    this->character_data[i]->vertices[3].position.y=this->character_data[i]->vertices[0].position.y+(current_height*factor);
  }
}*/

TextRenderer::TextRenderer(int _max_chars):max_chars(_max_chars), max_vertex(_max_chars*4), max_index(_max_chars*6), id_number(0), number_chars(0){
  int error=FT_Init_FreeType(&library);
  if(error){
    WEIGHT_ERROR("Text Renderer: Cannot initialise FreeType library code {0}", error);
    this->TextRenderer::~TextRenderer();
  }

  geometry.reserve(max_chars*0.01);
  for(int i=0; i<MAX_TEXTURES; i++){
    samplers[i]=i;
  }

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
  WEIGHT_SUCCESS("Text Renderer initialised");
}

TextRenderer::~TextRenderer(){
  FT_Done_FreeType(library);
  glDeleteVertexArrays(1, &vertex_array);
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteBuffers(1, &index_buffer);
}

void TextRenderer::submit(Text* text){
  if(number_chars>=max_chars){
    WEIGHT_WARNING("Text renderer: Max number of characters met. Cannot render text with id: {0}", text->id);
    return;
  }else{
    geometry.push_back(text);
    number_chars+=text->text.length();
  }
}
void TextRenderer::remove(Text* text){
  geometry.erase(std::find(geometry.begin(), geometry.end(), text));
}
void TextRenderer::render(glm::mat4 mvp, float ts){
  glBindVertexArray(vertex_array);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  TextShader::get()->bind();
  TextShader::get()->set_int_array("textures", samplers, MAX_TEXTURES);

  std::vector<Vertex> vertices;
  std::vector<unsigned int> texture_ids;
  std::vector<unsigned int>::iterator id_location;
  unsigned int number_textures=0;
  unsigned int opengl_texture_id=0;

  vertices.reserve(number_chars);
  for(int i=0; i<geometry.size(); i++){
    id_location=std::find(texture_ids.begin(), texture_ids.end(), geometry[i]->font->get_texture_id());
    if(id_location==texture_ids.end()){
      texture_ids.push_back(geometry[i]->font->get_texture_id());
      opengl_texture_id=number_textures++;
      glActiveTexture(GL_TEXTURE0+opengl_texture_id);
      glBindTexture(GL_TEXTURE_2D, geometry[i]->font->get_texture_id());
    }else{
      opengl_texture_id=*id_location;
    }

    for(int j=0; j<geometry[i]->character_data.size(); j++){
      for(int x=0; x<4; x++){
        geometry[i]->character_data[j].vertices[x].texture_slot=opengl_texture_id;
        vertices.push_back(geometry[i]->character_data[j].vertices[x]);
      }
    }

    if(number_textures+1==MAX_TEXTURES||i==geometry.size()-1){
      glBindVertexArray(vertex_array);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
      glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(Vertex), vertices.data());
      TextShader::get()->set_matrix("mvp", mvp);

      glDrawElements(GL_TRIANGLES, 6*vertices.size()*0.25, GL_UNSIGNED_INT, nullptr);

      vertices.clear();
      texture_ids.clear();
      number_textures=1;
    }
  }
}

Font* TextRenderer::load_font(std::string path){
  return new Font(path, NUMBER_FONT_CHARS, library);
}
Text* TextRenderer::generate_text(std::string text, Position2D pos, Font* font, Colour colour, float size, bool affect_mvp){
  return generate_text(text, {pos.x, pos.y, 0.0f}, font, colour, size, affect_mvp);
}
Text* TextRenderer::generate_text(std::string text, Position3D pos, Font* font, Colour colour, float size, bool affect_mvp){
  size=size*0.01f; //Basically mapping so the user can enter a normal number for the size

  Text* result=new Text;
  result->id=id_number++;
  result->text=text;
  result->pos=pos;
  result->font=font;
  result->colour=colour;
  result->size=size;

  result->character_data.reserve(text.length());

  Vector2D atlas_dimensions=font->get_atlas_dimensions();
  float x, y, x2, y2, w, h;
  x=pos.x;
  y=pos.y;
  for(int i=0; i<text.length(); i++){
    x2=x+font->characters[text[i]].bearing.x*size;
    y2=-y-font->characters[text[i]].bearing.y*size;
    w=font->characters[text[i]].size.x*size;
    h=font->characters[text[i]].size.y*size;

    x+=font->characters[text[i]].advance.x*size;
    y+=font->characters[text[i]].advance.y*size;

    if(!w||!h){
      continue;
    }

    CharacterRenderData c;

    c.vertices[0]={{x2, -y2, pos.z}, colour, {font->characters[text[i]].offset, 0.0f}, 0.0f, (affect_mvp)?1.0f:0.0f};
    c.vertices[1]={{x2+w, -y2, pos.z}, colour, {font->characters[text[i]].offset+font->characters[text[i]].size.x/atlas_dimensions.x, 0.0f}, 0.0f, (affect_mvp)?1.0f:0.0f};
    c.vertices[2]={{x2+w, -y2-h, pos.z}, colour, {font->characters[text[i]].offset+font->characters[text[i]].size.x/atlas_dimensions.x, font->characters[text[i]].size.y/atlas_dimensions.y}, 0.0f, (affect_mvp)?1.0f:0.0f};
    c.vertices[3]={{x2, -y2-h, pos.z}, colour, {font->characters[text[i]].offset, font->characters[text[i]].size.y/atlas_dimensions.y}, 0.0f, (affect_mvp)?1.0f:0.0f};

    result->character_data.push_back(c);
  }

  return result;
}
