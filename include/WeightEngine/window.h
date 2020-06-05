#ifndef WEIGHT_ENGINE__WINDOW_H
#define WEIGHT_ENGINE__WINDOW_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/event_system.h>
#include <WeightEngine/render_engine/orthographic_camera_controller.h>


#include <stb_image.h>

#if defined(WEIGHT_DESKTOP)
  #include <GLFW/glfw3.h>
  #include <glad/glad.h>
#elif defined(WEIGHT_ANDROID)
  #include <memory>
  #include <jni.h>
  #include <EGL/egl.h>
  #include <GLES/gl.h>
  #include <android/sensor.h>
  #include <WeightEngine/android_wrappers/android_native_app_glue.h>
  #include <WeightEngine/android_wrappers/android_structs.h>
#elif defined(WEIGHT_IOS)
#endif

#include <string>
#include <functional>

namespace Weight{
  class WEIGHT_API Window{
    friend class Weight::EventSystem;
  private:
    #if defined(WEIGHT_DESKTOP)
    GLFWwindow* _window;
    struct window_data{
      Window* parent;
    };

    window_data data;
    #elif defined(WEIGHT_ANDROID)
    Weight::Android::WeightState* weight_engine;
    bool _should_close;
    #endif
    int* _width;
    int* _height;
    std::string _icon_path;
    bool _has_focus;

    std::string _title;
    Weight::RenderEngine::OrthographicCameraController* _camera;
    Weight::EventSystem* _event_system;
  public:
    #if defined(WEIGHT_DESKTOP)
    Window(std::string title, int* width, int* height, std::string icon_path, Weight::RenderEngine::OrthographicCameraController* camera, Weight::EventSystem* event_system);
    #elif defined(WEIGHT_ANDROID)
    Window(std::string title, int* width, int* height, std::string icon_path, Weight::RenderEngine::OrthographicCameraController* camera, Weight::EventSystem* event_system, Weight::Android::WeightState* _weight_engine);
    #endif
    ~Window();

    void update();
    bool should_close();
    bool has_focus();
    void set_has_focus(bool val);
    void close();

    int* get_framebuffer();
    int* get_size();

    #ifdef WEIGHT_DESKTOP
    void set_size(int width, int height);
    std::string get_title();
    void set_title(std::string title);

    void hide_cursor();
    void show_cursor();
    #endif
  };
}


#endif
