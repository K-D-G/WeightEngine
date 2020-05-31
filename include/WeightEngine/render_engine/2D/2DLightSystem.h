#ifndef WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_LIGHT_SYSTEM_H
#define WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_LIGHT_SYSTEM_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/random.h>
#include <WeightEngine/render_engine/shaders/Light2D_shader.h>
#include <WeightEngine/render_engine/2D/2DLight.h>

#include <vector>
#include <algorithm>

#include <glm/glm.hpp>

namespace Weight{
  namespace RenderEngine{
    class WEIGHT_API LightSystem2D{
    private:
      unsigned int vertex_array;
      unsigned int vertex_buffer;
      unsigned int index_buffer;

      unsigned int max_lights;
      unsigned int max_vertex;
      unsigned int max_index;
    public:
      std::vector<Weight::RenderEngine::Light2D*> lights;

      LightSystem2D(unsigned int _max_lights);
      ~LightSystem2D();

      Weight::RenderEngine::Light2D* create_light(Weight::Position2D position, Weight::Colour colour, float size, bool affect_mvp=true);

      void render(glm::mat4 mvp, float ts);
      void submit(Weight::RenderEngine::Light2D* l);
      void remove(Weight::RenderEngine::Light2D* l);
    };
  }
}

#endif
