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
#include <WeightEngine/physics/physics_engine.h>
#include <WeightEngine/event_system.h>
#include <WeightEngine/window.h>
#include <WeightEngine/render_engine/renderer.h>
#include <WeightEngine/render_engine/orthographic_camera_controller.h>

#include <ALLibraries/alhelpers.h>

#ifdef WEIGHT_ANDROID
#include <cstdint>
#include <WeightEngine/android_wrappers/android_native_app_glue.h>
#include <WeightEngine/android_wrappers/android_structs.h>
#endif


#ifdef WEIGHT_IOS
#include <WeightEngine/ios_wrappers/Application.h>
#else
namespace WeightEngine{
  class WEIGHT_API Application{
    friend class Window;
  private:
    std::string _app_name;

    void _resize(int width, int height);

    int* _width;
    int* _height;

    //Data to only be used when first running
    WeightEngine::Colour background_colour;
    std::string background_path;
    std::string icon_path;
    WeightEngine::Physics::PhysicsWorldSetup pws;

    #ifdef WEIGHT_ANDROID
    WeightEngine::Android::WeightState* weight_engine;
    #endif
  public:
    WeightEngine::Window* window;
    WeightEngine::EventSystem* event_system;
    WeightEngine::RenderEngine::Renderer* renderer;
    WeightEngine::Physics::PhysicsEngine* physics_engine;
    WeightEngine::RenderEngine::OrthographicCameraController* camera;
    WeightEngine::Time* time;

    Application(std::string app_name, int width, int height, WeightEngine::Physics::PhysicsWorldSetup _pws, WeightEngine::Colour _background_colour={}, std::string _background_path="", std::string _icon_path="");
    ~Application();

    #ifdef WEIGHT_ANDROID
    void run(WeightEngine::Android::WeightState* _weight_engine);
    #else
    void run();
    #endif


    #ifdef WEIGHT_ANDROID
    void _handle_android_cmd(android_app* app, int32_t cmd);
    #endif

    virtual void on_start();
    virtual void on_update(float ts);
    virtual void on_shutdown();

    #if defined(WEIGHT_DESKTOP)
    virtual void on_key_press(WeightEngine::KeyEvent* e);
    virtual void on_mouse_press(WeightEngine::MousePressEvent* e);
    virtual void on_mouse_scroll(WeightEngine::MouseScrollEvent* e);
    virtual void on_gamepad_event(WeightEngine::Gamepad* g);
    #elif defined(WEIGHT_MOBILE)
    virtual void on_touch(WeightEngine::TouchEvent* e);
    #endif

  };

  extern WeightEngine::Application* create_application();
}
#endif


#endif
