#version 410

layout(location=0) out vec4 output_colour;

in vec4 colour;
in vec2 texture_coords;

void main(){
  //output_colour=vec4(colour.rgb, colour.a*(1.0-length(texture_coords)));
  output_colour=vec4(colour.rgb, colour.a*(pow(0.01, length(texture_coords))-0.01));
}
