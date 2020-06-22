#ifndef WEIGHT_ENGINE__RENDER_ENGINE__VERTEX_H
#define WEIGHT_ENGINE__RENDER_ENGINE__VERTEX_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>

namespace WeightEngine{
  namespace RenderEngine{
    struct WEIGHT_API Vertex{
      WeightEngine::Position3D position;
      WeightEngine::Colour colour;
      WeightEngine::Position2D texture_coords;
      float texture_slot; //Texture slot
      float affect_mvp;
    };
  }
}

#endif
