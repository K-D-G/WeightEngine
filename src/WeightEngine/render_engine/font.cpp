#include <WeightEngine/render_engine/font.h>

using namespace WeightEngine;
using namespace RenderEngine;

Font::Font(std::string font_path, int num_characters, FT_Library& lib):path(font_path), library(lib), number_characters(num_characters){
  characters.reserve(number_characters);
  reload_font(path);
}
Font::~Font(){
  FT_Done_Face(face);
}

void Font::reload_font(std::string font_path){
  if(Utils::textures_loaded[font_path]){
    WEIGHT_WARNING("Font: Trying to load a font that has already been loaded");
    return;
  }
  Utils::textures_loaded.erase(path);
  path=font_path;


  if(FT_New_Face(library, path.c_str(), 0, &face)){
    WEIGHT_ERROR("Font: Cannot load font: {0}", path);
  }

  FT_Set_Pixel_Sizes(face, 0, 100);

  int width=0;
  int height=0;
  int error;

  //for(int i=32; i<128; i++){
  for(int i=0; i<number_characters; i++){
    error=FT_Load_Char(face, i, FT_LOAD_RENDER);
    if(error){
      WEIGHT_ERROR("Font cannot load character {0} from {1} file. Reason: {2}", i, font_path.c_str(), DECODE_FREETYPE_ERROR(error));
      continue;
    }

    width+=face->glyph->bitmap.width;
    height=std::max(height, face->glyph->bitmap.rows);
  }

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

  int x=0;
  //for(int i=32; i<128; i++){
  for(int i=0; i<number_characters; i++){
    error=FT_Load_Char(face, i, FT_LOAD_RENDER);
    if(error){
      WEIGHT_ERROR("Font cannot load character {0} from {1} file. Reason: {2}", i, font_path.c_str(), DECODE_FREETYPE_ERROR(error));
      continue;
    }
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
    characters.push_back({(float)x/(float)width, {(float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows}, {(float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top}, {(float)(face->glyph->advance.x>>6), (float)(face->glyph->advance.y>>6)}});
    x+=face->glyph->bitmap.width;
  }

  atlas_dimensions={static_cast<float>(width), static_cast<float>(height)};
  Utils::textures_loaded[path]=texture_id;
}
std::string Font::get_font_path(){
  return path;
}
unsigned int Font::get_texture_id(){
  return texture_id;
}

Vector2D Font::get_atlas_dimensions(){
  return atlas_dimensions;
}
