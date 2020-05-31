#include <WeightEngine/render_engine/gui/gui_renderer.h>

using namespace Weight;
using namespace RenderEngine;
using namespace GUI;

GUIRenderer::GUIRenderer(int _max_widgets, Renderer2D* _Renderer_2D, TextRenderer* _text_renderer):max_widgets(_max_widgets), id_number(0){
  geometry.reserve(max_widgets);
  Renderer_2D=_Renderer_2D;
  text_renderer=_text_renderer;
  WEIGHT_SUCCESS("GUI Renderer initialised");
}
GUIRenderer::~GUIRenderer(){
  for(int i=0; i<geometry.size(); i++){
    geometry[i]->~Widget();
  }
}

void GUIRenderer::setup_widget(Widget* w){
  w->_setup(Renderer_2D, text_renderer);
}

void GUIRenderer::submit(Widget* w){
  if(geometry.size()>=max_widgets){
    WEIGHT_WARNING("GUI: Max number of widgets met. Cannot render Widget id: {0}", w->get_id());
    return;
  }else{
    geometry.push_back(w);
  }
}
void GUIRenderer::remove(Widget* w){
  geometry.erase(std::find(geometry.begin(), geometry.end(), w));
}
void GUIRenderer::render(float ts){
  for(int i=0; i<geometry.size(); i++){
    geometry[i]->render(ts);
  }
}
