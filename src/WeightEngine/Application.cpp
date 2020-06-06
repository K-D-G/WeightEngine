#include <WeightEngine/Application.h>

using namespace Weight;
using namespace RenderEngine;

#ifdef WEIGHT_ANDROID
using namespace Android;
#endif

Application::Application(std::string app_name, int width, int height, Colour _background_colour, std::string _background_path, std::string _icon_path){
  _app_name=app_name;
  Log::init(app_name);

  _width=new int;
  _height=new int;
  *(_width)=width;
  *(_height)=height;

  background_colour=_background_colour;
  background_path=_background_path;
  icon_path=_icon_path;
}

#ifdef WEIGHT_ANDROID
void Application::run(WeightState* _weight_engine){
  weight_engine=_weight_engine;
  WEIGHT_LOG("Weight engine initialising...");
  WEIGHT_SUCCESS("SPD Log initialised");

  time=Time::get();
  Random::init();

  OpenALHelpers::InitAL("");
  AudioUtils::set_distance_model(EXPONENT_DISTANCE);

  camera=new OrthographicCameraController((float)*(_width)/(float)*(_height), event_system, _width, _height);

  window=new Window(_app_name, _width, _height, icon_path, camera, event_system, weight_engine);

  renderer=new Renderer(_width, _height, background_colour, camera, background_path);

  WEIGHT_SUCCESS("Initialisation completed");
  WEIGHT_LOG("Starting application");
  this->on_start();
  while(!window->should_close()&&window->has_focus()){
    time->update();
    camera->on_update(time->get_time_step());
    this->on_update(time->get_time_step());
    renderer->render(time->get_time_step());
    window->update();
    event_system->update();
  }
  WEIGHT_LOG("Shutting down application");

  #ifdef WEIGHT_DEBUG
  WEIGHT_LOG("Saving profiling data");
  ProfileAggregator::get()->aggregate("profile.json");
  #endif

  OpenALHelpers::CloseAL();
  this->on_shutdown();
}
#else
void Application::run(){
  WEIGHT_LOG("Weight engine initialising...");
  WEIGHT_SUCCESS("SPD Log initialised");

  time=Time::get();
  Random::init();

  OpenALHelpers::InitAL("");
  AudioUtils::set_distance_model(EXPONENT_DISTANCE);

  std::function<void(KeyEvent*)> e=[=](KeyEvent* k){
    this->on_key_press(k);
  };

  std::function<void(MousePressEvent*)> e2=[=](MousePressEvent* mp){
    this->on_mouse_press(mp);
  };

  std::function<void(MouseScrollEvent*)> e3=[=](MouseScrollEvent* ms){
    this->on_mouse_scroll(ms);
  };

  std::function<void(Gamepad*)> e4=[=](Gamepad* g){
    this->on_gamepad_event(g);
  };

  event_system=new EventSystem(e, e2, e3, e4);

  camera=new OrthographicCameraController((float)*(_width)/(float)*(_height), event_system, _width, _height);

  window=new Window(_app_name, _width, _height, icon_path, camera, event_system);

  renderer=new Renderer(_width, _height, background_colour, camera, background_path);

  event_system->_setup(renderer->gui_renderer, camera->zoom_level);

  WEIGHT_SUCCESS("Initialisation completed");
  WEIGHT_LOG("Starting application");
  this->on_start();
  while(!window->should_close()&&window->has_focus()){
    time->update();
    camera->on_update(time->get_time_step());
    this->on_update(time->get_time_step());
    renderer->render(time->get_time_step());
    window->update();
    event_system->update();
  }
  WEIGHT_LOG("Shutting down application");

  #ifdef WEIGHT_DEBUG
  WEIGHT_LOG("Saving profiling data");
  ProfileAggregator::get()->aggregate("profile.json");
  #endif

  OpenALHelpers::CloseAL();
  this->on_shutdown();
}
#endif

#ifdef WEIGHT_ANDROID
void Application::_handle_android_cmd(android_app* app, int32_t cmd){
  WeightState* engine=(WeightEngine*)app->userData;
  switch(cmd){
    case APP_CMD_SAVE_STATE:
      engine->app->savedState=malloc(sizeof(SavedState));
      *((SavedState)engine->app->savedState)=engine->state;
      break;
    case APP_CMD_INIT_WINDOW:
      if(engine->app->window==nullptr){
        window=new Window(_app_name, _width, _height, icon_path, camera, event_system);
      }
      break;
    case APP_CMD_TERM_WINDOW:
      window->close();
      break;
    case APP_CMD_GAINED_FOCUS:
      window->set_has_focus(true);
      break;
    case APP_CMD_LOST_FOCUS:
      window->set_has_focus(false);
      break;
  }
}
#endif

void Application::_resize(int width, int height){
  renderer->camera->on_window_resize(width, height);
}

Application::~Application(){
  renderer->~Renderer();
  camera->~OrthographicCameraController();
  window->~Window();
  event_system->~EventSystem();
  WEIGHT_LOG("Application shutdown");
}

void Application::on_start(){
  WEIGHT_ERROR("Must define an on_start method in your application class");
}
void Application::on_update(float ts){
  WEIGHT_ERROR("Must define an on_update method in your application class");
}
void Application::on_shutdown(){
  WEIGHT_ERROR("Must define an on_shutdown method in your application class");
}

void Application::on_key_press(KeyEvent* e){

}
void Application::on_mouse_press(MousePressEvent* e){

}
void Application::on_mouse_scroll(MouseScrollEvent* e){

}
void Application::on_gamepad_event(Gamepad* g){

}
