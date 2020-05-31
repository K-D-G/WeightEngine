#include <WeightEngine/Application.h>

using namespace Weight;
using namespace RenderEngine;

Application::Application(){

}

#ifdef WEIGHT_USE_GLFW
void Application::run(std::string app_name, int width, int height, Colour background_colour, std::string background_path, std::string icon_path){
  _app_name=app_name;
  Log::init(app_name);
  WEIGHT_LOG("Weight engine initialising...");
  WEIGHT_SUCCESS("SPD Log initialised");

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

  time=Time::get();
  _width=new int;
  _height=new int;
  *(_width)=width;
  *(_height)=height;
  camera=new OrthographicCameraController((float)width/(float)height, event_system, _width, _height);

  window=new Window(_app_name, _width, _height, icon_path, camera, event_system);

  renderer=new Renderer(_width, _height, background_colour, camera, background_path);

  event_system->_setup(renderer->gui_renderer, camera->zoom_level);

  Random::init();

  OpenALHelpers::InitAL("");

  AudioUtils::set_distance_model(EXPONENT_DISTANCE);


  WEIGHT_SUCCESS("Initialisation completed");
  WEIGHT_LOG("Starting application");
  this->on_start();
  while(!window->should_close()){
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
void Application::run(std::string app_name){
  _app_name=app_name;
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
