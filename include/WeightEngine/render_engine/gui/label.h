#ifndef WEIGHT_ENGINE__RENDER_ENGINE__GUI__LABEL_H
#define WEIGHT_ENGINE__RENDER_ENGINE__GUI__LABEL_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/random.h>
#include <WeightEngine/render_engine/gui/widget.h>
#include <WeightEngine/render_engine/text_renderer.h>
#include <WeightEngine/render_engine/font.h>

#include <string>

namespace Weight{
  namespace RenderEngine{
    namespace GUI{
      class WEIGHT_API Label:public Widget{
      public:
        Weight::RenderEngine::Text* instance;
        std::string text;
        Weight::Position2D pos;
        Weight::RenderEngine::Font* font;
        Weight::Colour colour;
        float size;
      public:
        Label(std::string _text, Weight::Position2D _pos, Weight::RenderEngine::Font* _font, Weight::Colour _colour, float _size);
        ~Label();

        void set_position(Weight::Position2D _pos);
        void set_colour(Weight::Colour _colour);
        void set_size(float _size);
        void rotate(float _degrees);

        void on_setup() override;
      };
    }
  }
}

#endif
