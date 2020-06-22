#ifndef WEIGHT_ENGINE__RENDER_ENGINE__RENDERER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__RENDERER_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/maths_utils.h>
#include <WeightEngine/utils/audio_utils.h>
#include <WeightEngine/render_engine/2D/2DParticleSystem.h>
#include <WeightEngine/render_engine/2D/2DLightSystem.h>
#include <WeightEngine/render_engine/text_renderer.h>
#include <WeightEngine/render_engine/orthographic_camera_controller.h>
#include <WeightEngine/render_engine/2D/2D.h>
#include <WeightEngine/render_engine/gui/gui_renderer.h>

#if defined(WEIGHT_DESKTOP)
  #include <glad/glad.h>
#elif defined(WEIGHT_ANDROID)
  #include <EGL/egl.h>
  #include <GLES/gl.h>
#elif defined(WEIGHT_IOS)
  #include <MTLPP/mtlpp.hpp>
#endif

#include <string>

namespace WeightEngine{
  namespace RenderEngine{
    class WEIGHT_API Renderer{
    private:
      float* _background_colour;
      void set_background_image(std::string background_path);
    public:
      WeightEngine::RenderEngine::Renderer2D* Renderer_2D;
      WeightEngine::RenderEngine::ParticleSystem2D* particle_system;
      WeightEngine::RenderEngine::LightSystem2D* light_system;
      WeightEngine::RenderEngine::TextRenderer* text_renderer;
      WeightEngine::RenderEngine::GUI::GUIRenderer* gui_renderer;

      WeightEngine::RenderEngine::OrthographicCameraController* camera;
      Renderer(int* width, int* height, Colour background_colour, WeightEngine::RenderEngine::OrthographicCameraController* _camera, std::string background_path);
      ~Renderer();

      void set_background_colour(Colour background_colour);
      void prepare();
      void render(float ts);
    };
  }
}

#endif
