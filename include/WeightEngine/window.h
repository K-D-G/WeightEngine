#ifndef WEIGHT_ENGINE__WINDOW_H
#define WEIGHT_ENGINE__WINDOW_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/event_system.h>
#include <WeightEngine/render_engine/orthographic_camera_controller.h>


#include <stb_image.h>
#include <glad/glad.h>

#ifdef WEIGHT_DESKTOP
  #include <GLFW/glfw3.h>
#endif

#include <string>
#include <functional>

namespace Weight{
  class WEIGHT_API Window{
    friend class Weight::EventSystem;
  private:
    #ifdef WEIGHT_DESKTOP
    GLFWwindow* _window;
    int* _width;
    int* _height;
    std::string _icon_path;

    struct window_data{
      Window* parent;
    };

    window_data data;
    #endif

    std::string _title;
    Weight::RenderEngine::OrthographicCameraController* _camera;
    Weight::EventSystem* _event_system;
  public:
    #ifdef WEIGHT_DESKTOP
    Window(std::string title, int* width, int* height, std::string icon_path, Weight::RenderEngine::OrthographicCameraController* camera, Weight::EventSystem* event_system);
    #else
    Window(std::string title);
    #endif
    ~Window();

    void update();
    bool should_close();

    #ifdef WEIGHT_DESKTOP
    int* get_framebuffer();
    int* get_size();
    void set_size(int width, int height);
    std::string get_title();
    void set_title(std::string title);

    void hide_cursor();
    void show_cursor();

    #endif
  };
}


#endif
