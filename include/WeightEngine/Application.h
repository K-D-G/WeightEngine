#ifndef WEIGHT_ENGINE__APPLICATION_H
#define WEIGHT_ENGINE__APPLICATION_H

#include <string>
#include <functional>
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/random.h>
#include <WeightEngine/utils/time.h>
#include <WeightEngine/utils/audio_utils.h>
#include <WeightEngine/utils/profiling.h>
#include <WeightEngine/event_system.h>
#include <WeightEngine/window.h>
#include <WeightEngine/render_engine/renderer.h>
#include <WeightEngine/render_engine/orthographic_camera_controller.h>

#include <ALLibraries/alhelpers.h>

namespace Weight{
  class WEIGHT_API Application{
    friend class Window;
  private:
    std::string _app_name;

    void _resize(int width, int height);

    int* _width;
    int* _height;
  public:
    Weight::Window* window;
    Weight::EventSystem* event_system;
    Weight::RenderEngine::Renderer* renderer;
    Weight::RenderEngine::OrthographicCameraController* camera;
    Weight::Time* time;

    Application();
    ~Application();

    #ifdef WEIGHT_USE_GLFW
    void run(std::string app_name, int width, int height, Colour background_colour={}, std::string background_path="", std::string icon_path="");
    #else
    void run(std::string app_name);
    #endif

    virtual void on_start();
    virtual void on_update(float ts);
    virtual void on_shutdown();

    virtual void on_key_press(Weight::KeyEvent* e);
    virtual void on_mouse_press(Weight::MousePressEvent* e);
    virtual void on_mouse_scroll(Weight::MouseScrollEvent* e);
    virtual void on_gamepad_event(Weight::Gamepad* g);

  };
}


#endif
