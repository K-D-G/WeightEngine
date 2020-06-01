#include <WeightEngine/window.h>

using namespace Weight;

#ifdef WEIGHT_DESKTOP
Window::Window(std::string title, int* width, int* height, std::string icon_path, Weight::RenderEngine::OrthographicCameraController* camera, Weight::EventSystem* event_system):_title(title), _width(width), _height(height), _icon_path(icon_path), _camera(camera), _event_system(event_system){
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
  WEIGHT_SUCCESS("Window initialised");

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
#else
Window::Window(std::string title):_title(title){

}
#endif



Window::~Window(){
  #ifdef WEIGHT_DESKTOP
  WEIGHT_LOG("Shutting down window...");
  glfwDestroyWindow(_window);
  glfwTerminate();
  #endif
}

void Window::update(){
  #ifdef WEIGHT_DESKTOP
  glfwSwapBuffers(_window);
  glfwPollEvents();
  #endif
}

bool Window::should_close(){
  #ifdef WEIGHT_DESKTOP
  return glfwWindowShouldClose(_window);
  #endif
}

#ifdef WEIGHT_DESKTOP
int* Window::get_framebuffer(){
  int* result=new int[2];
  glfwGetFramebufferSize(_window, &result[0], &result[1]);
  return result;
}

int* Window::get_size(){
  int* result=new int[2];
  result[0]=*(_width);
  result[1]=*(_height);
  return result;
}

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
