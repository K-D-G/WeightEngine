#ifndef WEIGHT_ENGINE__RENDER_ENGINE__GUI__BUTTON_H
#define WEIGHT_ENGINE__RENDER_ENGINE__GUI__BUTTON_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/random.h>
#include <WeightEngine/render_engine/gui/widget.h>
#include <WeightEngine/render_engine/gui/label.h>
#include <WeightEngine/render_engine/2D/2D.h>
#include <WeightEngine/render_engine/text_renderer.h>
#include <functional>

namespace Weight{
  namespace RenderEngine{
    namespace GUI{
      class WEIGHT_API Button:public Widget{
      public:
        Weight::RenderEngine::GUI::Label* label_instance;
        Weight::RenderEngine::QuadData* quad_instance;
        Weight::Position2D pos;
        float width, height;
        Weight::Colour default_colour;
        Weight::Colour pressed_colour;
        std::function<void()> callback;
      public:
        Button(Weight::RenderEngine::GUI::Label* _label, Weight::Position2D _pos, float _width, float _height, Weight::Colour _default_colour, Weight::Colour _pressed_colour, std::function<void()> _callback);
        ~Button();

        void set_label(Weight::RenderEngine::GUI::Label* _label);
        void set_position(Weight::Position2D _pos);
        void set_size(float _width, float _height);
        void set_default_colour(Weight::Colour _default_colour);
        void set_pressed_colour(Weight::Colour _pressed_colour);
        void set_callback(std::function<void()> _callback);

        void on_mouse_press(Weight::MousePressEvent* e) override;
        void on_setup() override;
        void on_lose_focus() override;
        void on_gain_focus() override;
      };
    }
  }
}

#endif
