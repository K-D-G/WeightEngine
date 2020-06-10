#include <WeightEngine/window.h>

using namespace Weight;

#ifdef WEIGHT_DESKTOP
Window::Window(std::string title, int* width, int* height, std::string icon_path, Weight::RenderEngine::OrthographicCameraController* camera, Weight::EventSystem* event_system):_title(title), _width(width), _height(height), _icon_path(icon_path), _has_focus(true), _camera(camera), _event_system(event_system){
  if(!glfwInit()){
    WEIGHT_ERROR("GLFW WILL NOT INITIALISE");
    this->Window::~Window();
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  #if defined(WEIGHT_DEBUG) && !defined(__APPLE__)
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  #endif
  _window=glfwCreateWindow(*(_width), *(_height), _title.c_str(), NULL, NULL);
  if(!_window){
    WEIGHT_ERROR("GLFW FAILED CREATING WINDOW");
    this->Window::~Window();
  }
  data.parent=this;
  glfwSetWindowUserPointer(_window, &data);

  if(_icon_path.size()!=0){
    GLFWimage image_data[1];
    stbi_set_flip_vertically_on_load(1);
    int image_width, image_height, image_bpp;
    unsigned char* buffer=stbi_load(_icon_path.c_str(), &image_width, &image_height, &image_bpp, 4);
    image_data[0].pixels=buffer;
    image_data[0].width=image_width;
    image_data[0].height=image_height;
    glfwSetWindowIcon(_window, 1, image_data);
  }
  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    WEIGHT_ERROR("CANNOT LOAD OPENGL FUNCTIONS USING GLAD");
    this->Window::~Window();
  }
  WEIGHT_SUCCESS("OpenGL functions loaded");
  WEIGHT_LOG("OpenGL version: {0}", glGetString(GL_VERSION));

  int frame_buffer_width;
  int frame_buffer_height;
  glfwGetFramebufferSize(_window, &frame_buffer_width, &frame_buffer_height);
  glViewport(0, 0, frame_buffer_width, frame_buffer_height);
  WEIGHT_LOG("Set area OpenGL can render in to the size of the display");

  glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height){
    (*(Window::window_data*)glfwGetWindowUserPointer(window)).parent->set_size(width, height);
  });

  glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
  });

  glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int modifiers){
    (*(Window::window_data*)glfwGetWindowUserPointer(window)).parent->_event_system->_key_callback(key, action, modifiers);
  });

  glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int modifiers){
    (*(Window::window_data*)glfwGetWindowUserPointer(window)).parent->_event_system->_mouse_press_callback(button, action, modifiers);
  });

  glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset){
    (*(Window::window_data*)glfwGetWindowUserPointer(window)).parent->_event_system->_scroll_callback(xoffset, yoffset);
  });

  glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos){
    (*(Window::window_data*)glfwGetWindowUserPointer(window)).parent->_event_system->_cursor_pos_callback(xpos, ypos);
  });

  glfwSetJoystickCallback([](int jid, int event){
    GLFWwindow* window=glfwGetCurrentContext();
    if(window!=NULL){
      (*(Window::window_data*)glfwGetWindowUserPointer(window)).parent->_event_system->_gamepad_callback(jid, event);
    }
  });

  event_system->set_window(this);

  WEIGHT_SUCCESS("Set callbacks for the window");
  WEIGHT_SUCCESS("Window initialised");
}
#elif defined(WEIGHT_ANDROID)
Window::Window(std::string title, int* width, int* height, std::string icon_path, Weight::RenderEngine::OrthographicCameraController* camera, Weight::EventSystem* event_system, Weight::Android::WeightState* _weight_engine):_title(title), _width(width), _height(height), _should_close(false), _icon_path(icon_path), _camera(camera), _event_system(event_system), weight_engine(_weight_engine){
  const EGLint attribs[]={
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_NONE
  };
  EGLint w, h, format;
  EGLint number_configs;
  EGLConfig config=nullptr;
  EGLSurface surface;
  EGLContext context;
  EGLDisplay display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
  eglInitialize(display, nullptr, nullptr);
  eglChooseConfig(display, attribs, nullptr, 0, &number_configs);
  std::unique_ptr<EGLConfig[]> supported_configs(new EGLConfig[number_configs]);
  assert(supported_configs);
  eglChooseConfig(display, attribs, supported_configs.get(), number_configs, &number_configs);
  assert(number_configs);
  int i=0;
  for(; i<number_configs; i++){
    EGLConfig &cfg=supported_configs[i];
    EGLint r, g, b, d;
    if(eglGetConfigAttrib(display, cfg, EGL_RED_SIZE, &r)&&eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g)&&eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE, &b)&&eglGetConfigAttrib(display, cfg, EGL_DEPTH_SIZE, &d)&&r==8&&g==8&&b==8&&d==0){
      config=supported_configs[i];
      break;
    }
  }
  if(i==number_configs){
    config=supported_configs[0];
  }
  if(config==nullptr){
    WEIGHT_ERROR("Window: Cannot initialise a configuration for EGL on Android");
    this->Window::~Window();
  }

  eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
  surface=eglCreateWindowSurface(display, config, weight_engine->app->window, nullptr);
  context=eglCreateContext(display, config, nullptr, nullptr);
  if(eglMakeCurrent(display, surface, surface, context)==EGL_FALSE){
    WEIGHT_ERROR("Window: Cannot make an OpenGLES context for Android");
    this->Window::~Window();
  }

  eglQuerySurface(display, surface, EGL_WIDTH, &w);
  eglQuerySurface(display, surface, EGL_HEIGHT, &h);

  weight_engine->display=display;
  weight_engine->context=context;
  weight_engine->surface=surface;
  weight_engine->width=w;
  weight_engine->height=h;

  *(_width)=w;
  *(_height)=h;

  glViewport(0, 0, weight_engine->width, weight_engine->height);

  WEIGHT_SUCCESS("OpenGLES functions loaded");
  WEIGHT_LOG("OpenGLES version: {0}", glGetString(GL_VERSION));

  WEIGHT_SUCCESS("Set callbacks for the window");
  WEIGHT_SUCCESS("Window initialised");
}
#endif



Window::~Window(){
  WEIGHT_LOG("Shutting down window...");
  #if defined(WEIGHT_DESKTOP)
  glfwDestroyWindow(_window);
  glfwTerminate();
  #elif defined(WEIGHT_ANDROID)
  if(weight_engine->display!=EGL_NO_DISPLAY){
    eglMakeCurrent(weight_engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if(weight_engine->context!=EGL_NO_CONTEXT){
      eglDestroyContext(weight_engine->display, weight_engine->context);
    }
    if(weight_engine->surface!=EGL_NO_SURFACE){
      eglDestroySurface(weight_engine->display, weight_engine->surface);
    }
    eglTerminate(weight_engine->display);
  }
  weight_engine->display=EGL_NO_DISPLAY;
  weight_engine->context=EGL_NO_CONTEXT;
  weight_engine->surface=EGL_NO_SURFACE;
  #endif
}

void Window::update(){
  #if defined(WEIGHT_DESKTOP)
  glfwSwapBuffers(_window);
  glfwPollEvents();
  #elif defined(WEIGHT_ANDROID)
  eglSwapBuffers(weight_engine->display, weight_engine->surface);
  if(weight_engine->state->destroyRequested!=0){
    _should_close=true;
  }
  #endif
}

bool Window::should_close(){
  #if defined(WEIGHT_DESKTOP)
  return glfwWindowShouldClose(_window);
  #elif defined(WEIGHT_ANDROID)
  return _should_close;
  #endif
}

bool Window::has_focus(){
  #if defined(WEIGHT_DESKTOP)
  _has_focus=glfwGetWindowAttrib(_window, GLFW_FOCUSED);
  #endif
  return _has_focus;
}

void Window::close(){
  #if defined(WEIGHT_DESKTOP)
  glfwSetWindowShouldClose(_window, GLFW_TRUE);
  #elif defined(WEIGHT_ANDROID)
  _should_close=true;
  #endif
}

void Window::set_has_focus(bool val){
  _has_focus=val;
}



int* Window::get_framebuffer(){
  #if defined(WEIGHT_DESKTOP)
  int* result=new int[2];
  glfwGetFramebufferSize(_window, &result[0], &result[1]);
  return result;
  #elif defined(WEIGHT_ANDROID)
  return get_size();
  #endif
}

int* Window::get_size(){
  int* result=new int[2];
  result[0]=*(_width);
  result[1]=*(_height);
  return result;
}

#ifdef WEIGHT_DESKTOP
void Window::set_size(int width, int height){
  *(_width)=width;
  *(_height)=height;
  glfwSetWindowSize(_window, width, height);
  //int* frame_buffer=get_framebuffer();
  //glViewport(0, 0, frame_buffer[0], frame_buffer[1]);
  _camera->on_window_resize(width, height);
}

std::string Window::get_title(){
  return _title;
}

void Window::set_title(std::string title){
  WEIGHT_LOG("Window title changed");
  _title=title;
  glfwSetWindowTitle(_window, _title.c_str());
}

void Window::hide_cursor(){
  glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
void Window::show_cursor(){
  glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
#endif
