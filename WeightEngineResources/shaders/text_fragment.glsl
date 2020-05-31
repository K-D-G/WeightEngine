//For constants: https://www.khronos.org/opengl/wiki/Built-in_Variable_(GLSL)
#version 410 core

layout(location=0) out vec4 output_colour;

in vec4 colour;
in vec2 texture_coords;
in float texture_index;

uniform sampler2D textures[gl_MaxTextureImageUnits];

void main(){
  output_colour=vec4(1.0, 1.0, 1.0, texture(textures[int(texture_index)], texture_coords).r)*colour;
}
