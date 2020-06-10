#include <WeightEngine/event_system.h>
#include <WeightEngine/window.h>

using namespace Weight;
using namespace RenderEngine;
using namespace GUI;

#ifdef WEIGHT_ANDROID
using namespace Android;
#endif

#if defined(WEIGHT_DESKTOP)
EventSystem::EventSystem(std::function<void(KeyEvent*)> _on_key_press, std::function<void(MousePressEvent*)>_on_mouse_press, std::function<void(MouseScrollEvent*)>_on_mouse_scroll, std::function<void(Gamepad*)> _on_gamepad_event){
  _mouse_pos=new double[2];
  on_key_press=_on_key_press;
  on_mouse_press=_on_mouse_press;
  on_mouse_scroll=_on_mouse_scroll;
  on_gamepad_event=_on_gamepad_event;

  glfwUpdateGamepadMappings(Utils::load_file("WeightEngineResources/gamepad_mappings/default_mappings.txt").c_str());
  for(int i=0; i<GAMEPAD_LAST; i++){
    if(glfwJoystickPresent(i)){
      if(glfwJoystickIsGamepad(i)){
        Gamepad* gamepad=new Gamepad;
        gamepad->id=i;
        connected_gamepads.push_back(gamepad);
      }
    }
  }

  WEIGHT_SUCCESS("Event System initialised");
}
#elif defined(WEIGHT_MOBILE)
EventSystem(std::function<void(TouchEvent*)> _on_touch){
  on_touch=_on_touch;
}
#endif

EventSystem::~EventSystem(){

}

void EventSystem::update(){
  _events.clear();
  for(int i=0; i<connected_gamepads.size(); i++){
    on_gamepad_event(connected_gamepads[i]);
  }
}

std::vector<std::unique_ptr<Event>> EventSystem::get_events(){
  std::vector<std::unique_ptr<Event>> result=std::move(_events);
  _events.clear();
  return result;
}

#ifdef WEIGHT_DESKTOP
Position2D EventSystem::get_mouse_pos(){
  double* result=new double[2];
  int* window_dimensions=this->window->get_size();
  result[0]=(Maths::map(_mouse_pos[0]+window_dimensions[0]*0.5, 0.0f, window_dimensions[0], -1.0f, 1.0f, false))-1;
  result[1]=-(Maths::map(_mouse_pos[1]+window_dimensions[1]*0.5, 0.0f, window_dimensions[1], -1.0f, 1.0f, false))+1;

  Position2D r_pos={(float)result[0], (float)result[1]};
  r_pos.x=Maths::map(r_pos.x, -1.0f, 1.0f, -*(zoom_level), *(zoom_level), false);
  r_pos.y=Maths::map(r_pos.y, -1.0f, 1.0f, -*(zoom_level), *(zoom_level), false);
  return r_pos;
}

int EventSystem::get_key_state(int key){
  return glfwGetKey(this->window->_window, key);
}

bool EventSystem::check_modifier(int modifier, int var){
  for(int i=0; i<8; i++){
    if(CHECK_BIT(var, i)&&CHECK_BIT(modifier, i)){
      return true;
    }
  }
  return false;
}
#endif

void EventSystem::_setup(GUIRenderer* _gui_renderer, float* _zoom_level){
  gui_renderer=_gui_renderer;
  zoom_level=_zoom_level;
}

#ifdef WEIGHT_ANDROID
int32_t EventSystem::_handle_android_input(android_app* app, AInputEvent* event){
  WeightState* weight_engine=(WeightState*)app->userData;
  int32_t type=AInputEvent_getType(event);
  float x, y;
  int action;
  if(type==AINPUT_EVENT_TYPE_MOTION){
    switch(AInputEvent_getSource(event)){
      case AINPUT_SOURCE_TOUCHSCREEN:
        action=AKeyEvent_getAction(event)&AMOTION_EVENT_ACTION_MASK;
        _events.push_back(spdlog::details::make_unique<TouchEvent>(TOUCH, x, y, action));
        on_touch(GET_EVENT(KeyEvent, spdlog::details::make_unique<TouchEvent>(TOUCH, x, y, action)));
    }
  }
  return 0;
}

void EventSystem::_setup_android_sensors(WeightState* weight_engine){
  engine->sensor_manager=AcquireASensorManagerInstance(engine->app);
  engine->accelerometer=ASensorManager_getDefaultSensor(engine->sensor_manager, ASENSOR_TYPE_ACCELEROMETER);
  engine->sensor_event_queue=ASensorManager_createEventQueue(engine->sensor_manager, engine->app->looper, LOOPER_ID_USER, nullptr, nullptr);
}

void EventSystem::_check_android_sensors(WeightState* weight_engine){
  int ident;
  int events;
  android_poll_source* source;
  ASensorEvent event;

  while((ident=ALooper_pollAll(0, nullptr, &events, (void**)&source))>=0){
    if(source!=nullptr){
      source->process(state, source);
    }
    if(ident==LOOPER_ID_USER){
      if(engine->accelerometer!=nullptr){
        while(ASensorEventQueue_getEvents(engine->sensor_event_queue, &event, 1)>0){
          accelerometer_values={event.acceleration.x, event.acceleration.y, event.acceleration.z};
        }
      }
    }
  }
}

Vector3D EventSystem::get_accelerometer(){
  return accelerometer_values;
}

#endif

#ifdef WEIGHT_DESKTOP
void EventSystem::_key_callback(int key, int action, int modifiers){
  std::thread t(&EventSystem::_key_callback_gui, this, key, action, modifiers);
  _events.push_back(spdlog::details::make_unique<KeyEvent>(KEY, key, action, modifiers));
  on_key_press(GET_EVENT(KeyEvent, spdlog::details::make_unique<KeyEvent>(KEY, key, action, modifiers)));
  t.join();
}
void EventSystem::_key_callback_gui(int key, int action, int modifiers){
  for(int i=0; i<gui_renderer->geometry.size(); i++){
    gui_renderer->geometry[i]->_engine_on_key_press(GET_EVENT(KeyEvent, spdlog::details::make_unique<KeyEvent>(KEY, key, action, modifiers)));
  }
}

void EventSystem::_mouse_press_callback(int button, int action, int modifiers){
  std::thread t(&EventSystem::_mouse_press_callback_gui, this, button, action, modifiers);
  _events.push_back(spdlog::details::make_unique<MousePressEvent>(MOUSE_CLICK, button, action, modifiers, get_mouse_pos()));
  on_mouse_press(GET_EVENT(MousePressEvent, spdlog::details::make_unique<MousePressEvent>(MOUSE_CLICK, button, action, modifiers, get_mouse_pos())));
  t.join();
}
void EventSystem::_mouse_press_callback_gui(int button, int action, int modifiers){
  for(int i=0; i<gui_renderer->geometry.size(); i++){
    gui_renderer->geometry[i]->_engine_on_mouse_press(GET_EVENT(MousePressEvent, spdlog::details::make_unique<MousePressEvent>(MOUSE_CLICK, button, action, modifiers, get_mouse_pos())));
  }
}

void EventSystem::_scroll_callback(double xoffset, double yoffset){
  std::thread t(&EventSystem::_mouse_scroll_callback_gui, this, xoffset, yoffset);
  _events.push_back(spdlog::details::make_unique<MouseScrollEvent>(MOUSE_SCROLL, xoffset, yoffset));
  on_mouse_scroll(GET_EVENT(MouseScrollEvent, spdlog::details::make_unique<MouseScrollEvent>(MOUSE_SCROLL, xoffset, yoffset)));
  t.join();
}
void EventSystem::_mouse_scroll_callback_gui(double xoffset, double yoffset){
  for(int i=0; i<gui_renderer->geometry.size(); i++){
    gui_renderer->geometry[i]->_engine_on_mouse_scroll(GET_EVENT(MouseScrollEvent, spdlog::details::make_unique<MouseScrollEvent>(MOUSE_SCROLL, xoffset, yoffset)));
  }
}

void EventSystem::_cursor_pos_callback(double xpos, double ypos){
  _mouse_pos[0]=xpos;
  _mouse_pos[1]=ypos;
}


void EventSystem::_gamepad_callback(int jid, int event){
  if(event==GAMEPAD_CONNECTED){
    if(glfwJoystickIsGamepad(jid)){
      Gamepad* gamepad=new Gamepad;
      gamepad->id=jid;
      connected_gamepads.push_back(gamepad);
    }
  }else if(event==GAMEPAD_DISCONNECTED){
    for(int i=0; i<connected_gamepads.size(); i++){
      if(connected_gamepads[i]->id==jid){
        connected_gamepads.erase(connected_gamepads.begin()+i);
        return;
      }
    }
  }
}
#endif
