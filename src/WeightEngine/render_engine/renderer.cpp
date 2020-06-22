#include <WeightEngine/render_engine/renderer.h>

using namespace WeightEngine;
using namespace RenderEngine;
using namespace GUI;

Renderer::Renderer(int* width, int* height, Colour background_colour, OrthographicCameraController* _camera, std::string background_path){
  _background_colour=new float[4];
  set_background_colour(background_colour);

  if(background_path!=""){
    set_background_image(background_path);
  }

  #if defined(WEIGHT_DEBUG) && !defined(WEIGHT_MAC)
  GLint flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if(flags&GL_CONTEXT_FLAG_DEBUG_BIT){
    WEIGHT_LOG("Debug initialised");
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(Utils::opengl_error_message_callback, 0);
  }
  #endif

  camera=_camera;
  Renderer_2D=new Renderer2D(MAX_QUADS);
  particle_system=new ParticleSystem2D(MAX_PARTICLES);
  light_system=new LightSystem2D(MAX_LIGHTS);
  text_renderer=new TextRenderer(MAX_CHARS);
  gui_renderer=new GUIRenderer(MAX_WIDGETS, Renderer_2D, text_renderer);
  AudioUtils::set_subtitling_renderer(text_renderer);

  #if defined(WEIGHT_MAC)
  //For some reason OpenGL crashes on Apple without setting up a VAO at the start
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  #endif

  WEIGHT_SUCCESS("Renderer initialised");
}

Renderer::~Renderer(){
  WEIGHT_LOG("Renderer shutting down");
  this->Renderer_2D->~Renderer2D();
  this->particle_system->~ParticleSystem2D();
  this->light_system->~LightSystem2D();
  this->text_renderer->~TextRenderer();
  this->gui_renderer->~GUIRenderer();
}

void Renderer::set_background_colour(Colour background_colour){
  _background_colour[0]=background_colour.r;
  _background_colour[1]=background_colour.g;
  _background_colour[2]=background_colour.b;
  _background_colour[3]=background_colour.a;
}

void Renderer::set_background_image(std::string background_path){
  Renderer_2D->set_background_image(background_path);
}

void Renderer::prepare(){
  //glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glClearColor(_background_colour[0], _background_colour[1], _background_colour[2], _background_colour[3]);
  //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  Renderer_2D->render_background(camera->get_camera()->get_view_projection_matrix());
}

void Renderer::render(float ts){
  prepare();
  gui_renderer->render(ts);
  Renderer_2D->render(camera->get_camera()->get_view_projection_matrix(), ts);
  particle_system->render(camera->get_camera()->get_view_projection_matrix(), ts);
  text_renderer->render(camera->get_camera()->get_view_projection_matrix(), ts);
  light_system->render(camera->get_camera()->get_view_projection_matrix(), ts);
}
