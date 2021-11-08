#ifndef WEIGHT_ENGINE__RENDER_ENGINE__2D__QUAD_H
#define WEIGHT_ENGINE__RENDER_ENGINE__2D__QUAD_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/maths_utils.h>
#include <WeightEngine/render_engine/shader.h>
#include <WeightEngine/render_engine/shaders/basic_shader.h>
#include <WeightEngine/render_engine/texture_atlas.h>
#include <WeightEngine/render_engine/vertex.h>

#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

#include <cstdlib>

#if defined(WEIGHT_DESKTOP)
  #include <glad/glad.h>
#elif defined(WEIGHT_ANDROID)
  #include <EGL/egl.h>
  #include <GLES/gl.h>
#elif defined(WEIGHT_IOS)
#endif
#include <glm/glm.hpp>


namespace WeightEngine{
  namespace RenderEngine{
    struct WEIGHT_API Quad{
      int id;
      unsigned int texture_id;
      WeightEngine::Vector2D dimensions;
      WeightEngine::RenderEngine::Vertex vertices[4];
      //WeightEngine::Position3D centre_pos;

      void move(WeightEngine::Position3D translation);
      void move(WeightEngine::Position2D translation);
      void set_position(WeightEngine::Position3D position);
      void set_position(WeightEngine::Position2D position);
      void set_size(float width, float height);

      void rotate(float degrees);
      void flip(int axis);
      void scale(float factor);

      void set_texture(std::string path);
      void set_texture_from_atlas(WeightEngine::RenderEngine::SubTexture* texture);

      void fill(WeightEngine::Colour colour);
      inline void no_fill(){fill({0.0f, 0.0f, 0.0f, 0.0f});}
    };
  }
}


#endif
