#version 410

layout(location=0) in vec3 position;
layout(location=1) in vec4 vertex_colour;
layout(location=2) in vec2 vertex_texture_coords;
layout(location=3) in float vertex_texture_index;
layout(location=4) in float affect_mvp;

uniform mat4 mvp;

out vec4 colour;
out vec2 texture_coords;

void main(){
  colour=vertex_colour;
  texture_coords=vertex_texture_coords;
  if(affect_mvp==1.0f){
    gl_Position=mvp*vec4(position, 1.0);
  }else{
    gl_Position=vec4(position, 1.0);
  }
}
