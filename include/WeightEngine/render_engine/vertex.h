#ifndef WEIGHT_ENGINE__RENDER_ENGINE__VERTEX_H
#define WEIGHT_ENGINE__RENDER_ENGINE__VERTEX_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>

namespace Weight{
  namespace RenderEngine{
    struct WEIGHT_API Vertex{
      Weight::Position3D position;
      Weight::Colour colour;
      Weight::Position2D texture_coords;
      float texture_slot; //Texture slot
      float affect_mvp;
    };
  }
}

#endif
