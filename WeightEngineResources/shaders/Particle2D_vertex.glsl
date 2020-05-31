#version 410

layout(location=0) in vec3 position;
layout(location=1) in vec4 vertex_colour;

out vec4 colour;

uniform mat4 mvp;

void main(){
  gl_Position=mvp*vec4(position, 1.0);
  colour=vertex_colour;
}
