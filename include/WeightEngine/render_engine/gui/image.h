#ifndef WEIGHT_ENGINE__RENDER_ENGINE__GUI__IMAGE_H
#define WEIGHT_ENGINE__RENDER_ENGINE__GUI__IMAGE_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/random.h>
#include <WeightEngine/render_engine/gui/widget.h>
#include <WeightEngine/render_engine/2D/2D.h>

#include <string>


namespace Weight{
  namespace RenderEngine{
    namespace GUI{
      class WEIGHT_API Image:public Widget{
      public:
        std::string path;
        float width;
        float height;
        Weight::Position2D pos;

        Weight::RenderEngine::QuadData* instance;
      public:
        Image(std::string _path, Weight::Position2D _pos, float _width, float _height);
        ~Image();

        void set_texture(std::string _path);
        void set_size(float _width, float _height);
        void set_position(Weight::Position2D _pos);

        void on_setup() override;
      };
    }
  }
}

#endif
