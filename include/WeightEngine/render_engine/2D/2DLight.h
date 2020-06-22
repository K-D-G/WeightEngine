#ifndef WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_LIGHT_H
#define WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_LIGHT_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/render_engine/vertex.h>

namespace WeightEngine{
  namespace RenderEngine{
    class WEIGHT_API Light2D{
    private:
      WeightEngine::Position2D position;
      WeightEngine::Colour colour;
      float size;
      bool affect_mvp;
    public:
      WeightEngine::RenderEngine::Vertex vertices[4];

      Light2D(WeightEngine::Position2D _position, WeightEngine::Colour _colour, float _size, bool _affect_mvp=true);
      ~Light2D();

      void set_position(WeightEngine::Position2D pos);
      void move(WeightEngine::Vector2D translation);
      void set_colour(WeightEngine::Colour _colour);
      void set_size(float _size);

      WeightEngine::Position2D get_position();
      WeightEngine::Colour get_colour();
      float get_size();
    };
  }
}

#endif
