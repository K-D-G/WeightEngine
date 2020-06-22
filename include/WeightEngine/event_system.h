#ifndef WEIGHT_ENGINE__EVENT_SYSTEM_H
#define WEIGHT_ENGINE__EVENT_SYSTEM_H
#include <vector>
#include <utility>
#include <memory>
#include <functional>
#include <thread>

#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/keycodes.h>
#include <WeightEngine/utils/maths_utils.h>
#include <WeightEngine/render_engine/gui/gui_renderer.h>

#if defined(WEIGHT_DESKTOP)
#include <GLFW/glfw3.h>
#elif defined(WEIGHT_ANDROID)
#include <cstdint>
#include <WeightEngine/android_wrappers/android_util_functions.h>
#include <WeightEngine/android_wrappers/android_structs.h>
#include <WeightEngine/android_wrappers/android_native_app_glue.h>
#include <android/sensor.h>
#endif

#define GET_EVENT(type, x) static_cast<type*>(x.get())

namespace WeightEngine{
  namespace RenderEngine{namespace GUI{class WEIGHT_API GUIRenderer;}}
  struct WEIGHT_API Event{
    int type;
    inline Event(int _type):type(_type){}
  };

  struct WEIGHT_API KeyEvent:Event{
    int key;
    int action;
    int modifiers;
    inline KeyEvent(int _type, int _key, int _action, int _modifiers):Event(_type), key(_key), action(_action), modifiers(_modifiers){}
  };

  struct WEIGHT_API MousePressEvent:Event{
    int button;
    int action;
    int modifiers;
    WeightEngine::Position2D mouse_position;
    inline MousePressEvent(int _type, int _button, int _action, int _modifiers, WeightEngine::Position2D _mouse_pos):Event(_type), button(_button), action(_action), modifiers(_modifiers), mouse_position(_mouse_pos){}
  };

  struct WEIGHT_API MouseScrollEvent:Event{
    double xoffset;
    double yoffset;
    inline MouseScrollEvent(int _type, double _xoffset, double _yoffset):Event(_type), xoffset(_xoffset), yoffset(_yoffset){}
  };

  struct WEIGHT_API TouchEvent:Event{
    float x, y;
    int action;
    inline TouchEvent(int _type, float _x, float _y, int _action):Event(_type), x(_x), y(_y), action(_action){}
  };

  struct WEIGHT_API Gamepad{
    int id;
    unsigned char buttons[15];
    float axes[6];
  };

  class WEIGHT_API Window;

  class WEIGHT_API EventSystem{
  private:
    std::vector<std::unique_ptr<Event>> _events;
    WeightEngine::Window* window;
    WeightEngine::RenderEngine::GUI::GUIRenderer* gui_renderer;
    float* zoom_level;

    #if defined(WEIGHT_DESKTOP)
    double* _mouse_pos;

    std::function<void(KeyEvent*)> on_key_press;
    std::function<void(MousePressEvent*)> on_mouse_press;
    std::function<void(MouseScrollEvent*)> on_mouse_scroll;
    std::function<void(Gamepad*)> on_gamepad_event;
    #elif defined(WEIGHT_MOBILE)
    WeightEngine::Vector3D accelerometer_values;
    accelerom
    std::function<void(TouchEvent*)> on_touch;
    #endif

    std::vector<Gamepad*> connected_gamepads;
  public:
    #if defined(WEIGHT_DESKTOP)
    EventSystem(std::function<void(KeyEvent*)> _on_key_press, std::function<void(MousePressEvent*)>_on_mouse_press, std::function<void(MouseScrollEvent*)>_on_mouse_scroll, std::function<void(Gamepad*)> _on_gamepad_event);
    #elif defined(WEIGHT_MOBILE)
    EventSystem(std::function<void(TouchEvent*)> _on_touch);
    #endif
    ~EventSystem();

    void update();
    std::vector<std::unique_ptr<Event>> get_events();

    #ifdef WEIGHT_DESKTOP
    WeightEngine::Position2D get_mouse_pos();
    int get_key_state(int key);
    bool check_modifier(int modifier, int var);
    #endif

    void _setup(WeightEngine::RenderEngine::GUI::GUIRenderer* _gui_renderer, float* _zoom_level);

    #ifdef WEIGHT_ANDROID
    int32_t _handle_android_input(android_app* app, AInputEvent* event);
    void _setup_android_sensors(WeightEngine::Android::WeightState* weight_engine);
    void _check_android_sensors(WeightEngine::Android::WeightState* weight_engine);

    WeightEngine::Vector3D get_accelerometer();
    #endif
  private:
    #ifdef WEIGHT_DESKTOP
    void _key_callback(int key, int action, int modifiers);
    void _key_callback_gui(int key, int action, int modifiers);

    void _mouse_press_callback(int button, int action, int modifiers);
    void _mouse_press_callback_gui(int button, int action, int modifiers);

    void _scroll_callback(double xoffset, double yoffset);
    void _mouse_scroll_callback_gui(double xoffset, double yoffset);

    void _cursor_pos_callback(double xpos, double ypos);
    void _gamepad_callback(int jid, int event);
    #endif

    inline void set_window(WeightEngine::Window* _window){window=_window;}

    friend class WeightEngine::Window;
  };
}

#endif
