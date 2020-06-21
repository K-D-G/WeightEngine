//For constants: https://www.khronos.org/opengl/wiki/Built-in_Variable_(GLSL)
#version 410 core

layout(location=0) out vec4 output_colour;

in vec4 colour;
in vec2 texture_coords;
in float texture_index;

uniform sampler2D textures[gl_MaxTextureImageUnits];

void main(){
  if(texture_index==0.0f){
    output_colour=colour;
  }else{
    output_colour=texture(textures[int(texture_index)], texture_coords);
  }
}
