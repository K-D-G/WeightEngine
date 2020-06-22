#include <WeightEngine/render_engine/texture_atlas.h>

using namespace WeightEngine;
using namespace RenderEngine;

TextureAtlas::TextureAtlas(std::string texture_path, int texture_width, int texture_height){
  reload_texture(texture_path, texture_width, texture_height);
}
TextureAtlas::TextureAtlas(std::string name, int width, int height, int texture_width, int texture_height, unsigned char* buffer){
  reload_texture(name, width, height, texture_width, texture_height, buffer);
}
TextureAtlas::~TextureAtlas(){

}

std::string TextureAtlas::get_path(){
  return path;
}
unsigned int TextureAtlas::get_texture_id(){
  return texture_id;
}
void TextureAtlas::reload_texture(std::string texture_path, int texture_width, int texture_height){
  Utils::Image* image=Utils::load_image(texture_path);
  image_width=image->width;
  image_height=image->height;
  text_width=texture_width;
  text_height=texture_height;
  texture_id=Utils::load_opengl_texture(image);

  textures_wide=(image_width/text_width);
  textures_tall=(image_height/text_height);
  number_textures=textures_wide*textures_tall;
}
void TextureAtlas::reload_texture(std::string name, int width, int height, int texture_width, int texture_height, unsigned char* buffer){
  image_width=width;
  image_height=height;
  text_width=texture_width;
  text_height=texture_height;
  texture_id=Utils::load_opengl_texture(name, width, height, buffer);

  textures_wide=(image_width/text_width);
  textures_tall=(image_height/text_height);
  number_textures=textures_wide*textures_tall;
}

SubTexture* TextureAtlas::get_texture(int x, int y){
  for(int i=0; i<generated_coords.size(); i++){
    if(generated_coords[i]->x==x&&generated_coords[i]->y==y){
      return generated_coords[i];
    }
  }
  SubTexture* result=new SubTexture;

  result->texture_coords[0]=(x*text_width)/image_width;
  result->texture_coords[1]=(y*text_height)/image_height;

  result->texture_coords[2]=((x*text_width)+text_width)/image_width;
  result->texture_coords[3]=(y*text_height)/image_height;

  result->texture_coords[4]=((x*text_width)+text_width)/image_width;
  result->texture_coords[5]=((y*text_height)+text_height)/image_height;

  result->texture_coords[6]=(x*text_width)/image_width;
  result->texture_coords[7]=((y*text_height)+text_height)/image_height;


  result->texture_id=texture_id;
  result->x=x;
  result->y=y;
  generated_coords.push_back(result);

  return result;
}
