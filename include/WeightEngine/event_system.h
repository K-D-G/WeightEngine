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
#include <WeightEngine/android_wrappers/android_structs.h>
#include <WeightEngine/android_wrappers/android_native_app_glue.h>
#endif

#define GET_EVENT(type, x) static_cast<type*>(x.get())

namespace Weight{
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
    Weight::Position2D mouse_position;
    inline MousePressEvent(int _type, int _button, int _action, int _modifiers, Weight::Position2D _mouse_pos):Event(_type), button(_button), action(_action), modifiers(_modifiers), mouse_position(_mouse_pos){}
  };

  struct WEIGHT_API MouseScrollEvent:Event{
    double xoffset;
    double yoffset;
    inline MouseScrollEvent(int _type, double _xoffset, double _yoffset):Event(_type), xoffset(_xoffset), yoffset(_yoffset){}
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
    double* _mouse_pos;
    Weight::Window* window;
    Weight::RenderEngine::GUI::GUIRenderer* gui_renderer;
    float* zoom_level;

    std::function<void(KeyEvent*)> on_key_press;
    std::function<void(MousePressEvent*)> on_mouse_press;
    std::function<void(MouseScrollEvent*)> on_mouse_scroll;
    std::function<void(Gamepad*)> on_gamepad_event;

    std::vector<Gamepad*> connected_gamepads;
  public:
    EventSystem(std::function<void(KeyEvent*)> _on_key_press, std::function<void(MousePressEvent*)>_on_mouse_press, std::function<void(MouseScrollEvent*)>_on_mouse_scroll, std::function<void(Gamepad*)> _on_gamepad_event);
    ~EventSystem();

    void update();
    std::vector<std::unique_ptr<Event>> get_events();
    Weight::Position2D get_mouse_pos();

    int get_key_state(int key);

    bool check_modifier(int modifier, int var);

    void _setup(Weight::RenderEngine::GUI::GUIRenderer* _gui_renderer, float* _zoom_level);

    #ifdef WEIGHT_ANDROID
    void _handle_android_input(android_app* app, AInputEvent* event);
    #endif
  private:
    void _key_callback(int key, int action, int modifiers);
    void _key_callback_gui(int key, int action, int modifiers);

    void _mouse_press_callback(int button, int action, int modifiers);
    void _mouse_press_callback_gui(int button, int action, int modifiers);

    void _scroll_callback(double xoffset, double yoffset);
    void _mouse_scroll_callback_gui(double xoffset, double yoffset);

    void _cursor_pos_callback(double xpos, double ypos);
    void _gamepad_callback(int jid, int event);

    inline void set_window(Weight::Window* _window){window=_window;}

    friend class Weight::Window;
  };
}

#endif
