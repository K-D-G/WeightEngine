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

namespace WeightEngine{
  namespace RenderEngine{
    namespace GUI{
      class WEIGHT_API Label:public Widget{
      public:
        WeightEngine::RenderEngine::Text* instance;
        std::string text;
        WeightEngine::Position2D pos;
        WeightEngine::RenderEngine::Font* font;
        WeightEngine::Colour colour;
        float size;
      public:
        Label(std::string _text, WeightEngine::Position2D _pos, WeightEngine::RenderEngine::Font* _font, WeightEngine::Colour _colour, float _size);
        ~Label();

        void set_position(WeightEngine::Position2D _pos);
        void set_colour(WeightEngine::Colour _colour);
        void set_size(float _size);
        void rotate(float _degrees);

        void on_setup() override;
      };
    }
  }
}

#endif
