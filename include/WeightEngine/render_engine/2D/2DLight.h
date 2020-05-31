#ifndef WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_LIGHT_H
#define WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_LIGHT_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/render_engine/vertex.h>

namespace Weight{
  namespace RenderEngine{
    class WEIGHT_API Light2D{
    private:
      Weight::Position2D position;
      Weight::Colour colour;
      float size;
      bool affect_mvp;
    public:
      Weight::RenderEngine::Vertex vertices[4];

      Light2D(Weight::Position2D _position, Weight::Colour _colour, float _size, bool _affect_mvp=true);
      ~Light2D();

      void set_position(Weight::Position2D pos);
      void move(Weight::Vector2D translation);
      void set_colour(Weight::Colour _colour);
      void set_size(float _size);

      Weight::Position2D get_position();
      Weight::Colour get_colour();
      float get_size();
    };
  }
}

#endif
