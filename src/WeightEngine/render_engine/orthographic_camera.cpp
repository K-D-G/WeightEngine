#include <WeightEngine/render_engine/orthographic_camera.h>

using namespace Weight;
using namespace RenderEngine;

//Submit aspect ratio
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, int* _screen_width, int* _screen_height):projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view_matrix(1.0f), screen_width(_screen_width), screen_height(_screen_height){
  view_projection_matrix=projection_matrix*view_matrix;
}
OrthographicCamera::~OrthographicCamera(){

}

void OrthographicCamera::set_projection(float left, float right, float bottom, float top){
    projection_matrix=glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    view_projection_matrix=projection_matrix*view_matrix;
}

void OrthographicCamera::set_position(glm::vec3 pos){
  position=pos;
  recalculate_view_matrix();
}

void OrthographicCamera::set_rotation(float rot){
  rotation=rot;
  recalculate_view_matrix();
}

glm::vec3 OrthographicCamera::get_position(){
  return position;
}
float OrthographicCamera::get_rotation(){
  return rotation;
}

glm::mat4 OrthographicCamera::get_projection_matrix(){
  return projection_matrix;
}
glm::mat4 OrthographicCamera::get_view_matrix(){
  return view_matrix;
}
glm::mat4 OrthographicCamera::get_view_projection_matrix(){
  return view_projection_matrix;
}

void OrthographicCamera::recalculate_view_matrix(){
  glm::mat4 transform=glm::translate(glm::mat4(1.0f), position)*glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
  view_matrix=glm::inverse(transform);
  view_projection_matrix=projection_matrix*view_matrix;
}
