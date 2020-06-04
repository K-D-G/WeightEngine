#ifndef WEIGHT_ENGINE__RENDER_ENGINE__GUI__GUI_RENDERER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__GUI__GUI_RENDERER_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/render_engine/vertex.h>
#include <WeightEngine/render_engine/gui/widget.h>
#include <WeightEngine/render_engine/2D/2D.h>
#include <WeightEngine/render_engine/text_renderer.h>
#include <WeightEngine/render_engine/shaders/basic_shader.h>

#include <vector>
#include <algorithm>

#if defined(WEIGHT_DESKTOP)
  #include <glad/glad.h>
#elif defined(WEIGHT_ANDROID)
  #include <EGL/egl.h>
  #include <GLES/gl.h>
#elif defined(WEIGHT_IOS)
#endif
#include <glm/glm.hpp>

namespace Weight{
  namespace RenderEngine{
    namespace GUI{
      class WEIGHT_API Widget;

      class WEIGHT_API GUIRenderer{
      public:
        std::vector<Weight::RenderEngine::GUI::Widget*> geometry;
      private:
        int id_number;
        int max_widgets;
        Weight::RenderEngine::Renderer2D* Renderer_2D;
        Weight::RenderEngine::TextRenderer* text_renderer;
      public:
        GUIRenderer(int _max_widgets, Weight::RenderEngine::Renderer2D* _Renderer_2D, Weight::RenderEngine::TextRenderer* _text_renderer);
        ~GUIRenderer();

        void setup_widget(Weight::RenderEngine::GUI::Widget* w);
        void submit(Weight::RenderEngine::GUI::Widget* w);
        void remove(Weight::RenderEngine::GUI::Widget* w);
        void render(float ts);
      };
    }
  }
}

#endif
