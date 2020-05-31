#ifndef WEIGHT_ENGINE__RENDER_ENGINE__GUI__WIDGET_H
#define WEIGHT_ENGINE__RENDER_ENGINE__GUI__WIDGET_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/event_system.h>
#include <WeightEngine/render_engine/2D/2D.h>
#include <WeightEngine/render_engine/text_renderer.h>
#include <WeightEngine/render_engine/vertex.h>

namespace Weight{
  struct KeyEvent;
  struct MousePressEvent;
  struct MouseScrollEvent;
  namespace RenderEngine{
    namespace GUI{
      class WEIGHT_API Widget{
      private:
        int id;
        Weight::Position2D bounding_box[4]; //bottom left, bottom right, top right, top left
        bool focused;
      public:
        Weight::RenderEngine::Renderer2D* Renderer_2D;
        Weight::RenderEngine::TextRenderer* text_renderer;

        Widget(int _id);
        ~Widget();

        void update_bounds(Weight::Position2D b[4]);

        void _engine_on_key_press(Weight::KeyEvent* e);
        void _engine_on_mouse_press(Weight::MousePressEvent* e);
        void _engine_on_mouse_scroll(Weight::MouseScrollEvent* e);
        void _setup(Weight::RenderEngine::Renderer2D* _Renderer_2D, Weight::RenderEngine::TextRenderer* _text_renderer);

        bool has_focus();
        virtual void render(float ts);
        virtual void on_key_press(Weight::KeyEvent* e);
        virtual void on_mouse_press(Weight::MousePressEvent* e);
        virtual void on_mouse_scroll(Weight::MouseScrollEvent* e);
        virtual void on_setup();
        virtual void on_lose_focus();
        virtual void on_gain_focus();
        int get_id();
      };
    }
  }
}

#endif
