#ifndef WEIGHT_ENGINE__RENDER_ENGINE__ORTHOGRAPHIC_CAMERA_CONTROLLER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__ORTHOGRAPHIC_CAMERA_CONTROLLER_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/keycodes.h>
#include <WeightEngine/render_engine/orthographic_camera.h>
#include <WeightEngine/event_system.h>

#include <glm/glm.hpp>
#include <algorithm>

namespace WeightEngine{
  namespace RenderEngine{
    class WEIGHT_API OrthographicCameraController{
    public:
      float aspect_ratio;
      float* zoom_level=new float(1.0f);
      WeightEngine::EventSystem* event_system;
      WeightEngine::RenderEngine::OrthographicCamera* camera;

      glm::vec3 camera_position=glm::vec3(0, 0, 0);
      float camera_rotation=0.0f;

      float camera_translation_speed=5.0f;
      float camera_rotation_speed=180.0f;
    public:
      OrthographicCameraController(float _aspect_ratio, EventSystem* _event_system, int* _screen_width, int* _screen_height);

      void on_update(float ts);

      void on_mouse_scroll(WeightEngine::MouseScrollEvent* mse);
      void on_window_resize(int width, int height);

      OrthographicCamera* get_camera();
    };
  }
}

#endif
