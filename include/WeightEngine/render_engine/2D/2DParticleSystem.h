#ifndef WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_PARTICLE_SYSTEM_H
#define WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_PARTICLE_SYSTEM_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/random.h>
#include <WeightEngine/render_engine/shaders/Particle2D_shader.h>

#include <vector>
#include <cstdlib>
#include <cmath>

#if defined(WEIGHT_DESKTOP)
  #include <glad/glad.h>
#elif defined(WEIGHT_ANDROID)
  #include <EGL/egl.h>
  #include <GLES/gl.h>
#elif defined(WEIGHT_IOS)
#endif
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

//Based off of the cherno's tutorial
namespace WeightEngine{
  namespace RenderEngine{
    struct WEIGHT_API Particle2D{
      WeightEngine::Position3D position;
      WeightEngine::Vector2D velocity, velocity_variation;
      WeightEngine::Colour begin_colour, end_colour;

      float begin_size, end_size, size_variation;

      float life_time=1.0f;
      float life_remaining=0.0f;

      float rotation=0.0f;

      bool active=false;
    };

    struct WEIGHT_API ParticleVertexRenderBuffer{
      WeightEngine::Position3D position;
      WeightEngine::Colour colour;
    };

    class WEIGHT_API ParticleSystem2D{
    private:
      unsigned int vertex_array;
      unsigned int vertex_buffer;
      unsigned int index_buffer;

      unsigned int max_particles;
      unsigned int max_index;
      unsigned int particle_index;
    public:
      std::vector<Particle2D*> particle_pool;

      ParticleSystem2D(unsigned int _max_particles);
      ~ParticleSystem2D();

      Particle2D* create_particle(WeightEngine::Position2D position, WeightEngine::Vector2D velocity, WeightEngine::Vector2D velocity_variation, WeightEngine::Colour begin_colour, WeightEngine::Colour end_colour, float begin_size, float end_size, float size_variation, float life_time=1.0f);
      Particle2D* create_particle(WeightEngine::Position3D position, WeightEngine::Vector2D velocity, WeightEngine::Vector2D velocity_variation, WeightEngine::Colour begin_colour, WeightEngine::Colour end_colour, float begin_size, float end_size, float size_variation, float life_time=1.0f);

      void render(glm::mat4 mvp, float ts);
      void emit(Particle2D* p);
    };
  }
}

#endif
