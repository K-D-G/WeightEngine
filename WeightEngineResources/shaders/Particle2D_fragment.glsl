//For constants: https://www.khronos.org/opengl/wiki/Built-in_Variable_(GLSL)
#version 410

layout(location=0) out vec4 output_colour;

in vec4 colour;

void main(){
  output_colour=colour;
}
