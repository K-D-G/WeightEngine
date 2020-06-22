#include <WeightEngine/render_engine/gui/widget.h>

using namespace WeightEngine;
using namespace RenderEngine;
using namespace GUI;

Widget::Widget(int _id):id(_id){

}
Widget::~Widget(){

}

void Widget::update_bounds(Position2D b[4]){
  for(int i=0; i<4; i++){
    bounding_box[i]=b[i];
  }
}

void Widget::_engine_on_key_press(KeyEvent* e){
  if(focused){
    on_key_press(e);
  }
}
void Widget::_engine_on_mouse_press(MousePressEvent* e){
  bool is_focused=(bounding_box[0].x>e->mouse_position.x&&bounding_box[1].x<e->mouse_position.x&&bounding_box[0].y<e->mouse_position.y&&bounding_box[2].y>e->mouse_position.y);
  if(is_focused==false&&is_focused==true){
    on_lose_focus();
  }else{
    on_gain_focus();
  }
  focused=is_focused;
  if(focused){
    on_mouse_press(e);
  }
}
void Widget::_engine_on_mouse_scroll(MouseScrollEvent* e){
  if(focused){
    on_mouse_scroll(e);
  }
}

void Widget::_setup(Renderer2D* _Renderer_2D, TextRenderer* _text_renderer){
  Renderer_2D=_Renderer_2D;
  text_renderer=_text_renderer;
  on_setup();
}

void Widget::render(float ts){
  WEIGHT_ERROR("Widget id: {0}. Must define a render method for this widget type", id);
}

bool Widget::has_focus(){
  return focused;
}

void Widget::on_key_press(KeyEvent* e){

}
void Widget::on_mouse_press(MousePressEvent* e){

}
void Widget::on_mouse_scroll(MouseScrollEvent* e){

}
void Widget::on_setup(){

}

void Widget::on_lose_focus(){

}
void Widget::on_gain_focus(){

}

int Widget::get_id(){
  return id;
}
