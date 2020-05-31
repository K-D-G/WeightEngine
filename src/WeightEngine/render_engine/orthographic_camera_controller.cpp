#include <WeightEngine/render_engine/orthographic_camera_controller.h>

using namespace Weight;
using namespace RenderEngine;

OrthographicCameraController::OrthographicCameraController(float _aspect_ratio, EventSystem* _event_system, int* _screen_width, int* _screen_height):aspect_ratio(_aspect_ratio), event_system(_event_system){
  camera=new OrthographicCamera(-aspect_ratio**(zoom_level), aspect_ratio**(zoom_level), -*(zoom_level), *(zoom_level), _screen_width, _screen_height);
}

void OrthographicCameraController::on_update(float ts){
  if(event_system->get_key_state(KEY_A)==PRESS||event_system->get_key_state(KEY_A)==REPEAT){
    camera_position.x-=camera_translation_speed*ts;
  }

  if(event_system->get_key_state(KEY_D)==PRESS||event_system->get_key_state(KEY_D)==REPEAT){
    camera_position.x+=camera_translation_speed*ts;
  }

  if(event_system->get_key_state(KEY_W)==PRESS||event_system->get_key_state(KEY_W)==REPEAT){
    camera_position.y+=camera_translation_speed*ts;
  }

  if(event_system->get_key_state(KEY_S)==PRESS||event_system->get_key_state(KEY_S)==REPEAT){
    camera_position.y-=camera_translation_speed*ts;
  }

  if(event_system->get_key_state(KEY_Q)==PRESS||event_system->get_key_state(KEY_Q)==REPEAT){
    camera_rotation+=camera_rotation_speed*ts;
  }

  if(event_system->get_key_state(KEY_E)==PRESS||event_system->get_key_state(KEY_E)==REPEAT){
    camera_rotation-=camera_rotation_speed*ts;
  }

  camera->set_position(camera_position);
  camera->set_rotation(camera_rotation);

  camera_translation_speed=*(zoom_level);
}

void OrthographicCameraController::on_mouse_scroll(MouseScrollEvent* mse){
  *(zoom_level)-=mse->yoffset*0.25f;
  *(zoom_level)=std::max(*(zoom_level), 0.25f);
  camera->set_projection(-aspect_ratio**(zoom_level), aspect_ratio**(zoom_level), -*(zoom_level), *(zoom_level));
}

void OrthographicCameraController::on_window_resize(int width, int height){
  aspect_ratio=(float)width/(float)height;
  camera->set_projection(-aspect_ratio**(zoom_level), aspect_ratio**(zoom_level), -*(zoom_level), *(zoom_level));
}

OrthographicCamera* OrthographicCameraController::get_camera(){
  return camera;
}
