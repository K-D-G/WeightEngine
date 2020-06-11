#ifndef WEIGHT_ENGINE__RENDER_ENGINE__FRAME_BUFFER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__FRAME_BUFFER_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>

#include <glad/glad.h>

//Edit the max things in core.h to account for different platforms

namespace Weight{
  namespace RenderEngine{
    struct FramebufferData{
      unsigned int width, height;
      unsigned int samples=1;
    };
    class Framebuffer{
    private:
      FramebufferData* data;
      unsigned int id, colour_attachment, depth_attachment;
    public:
      Framebuffer(FramebufferData* _data);
      ~Framebuffer();

      void rebuild();

      void bind();
      void unbind();

      unsigned int get_colour_attachment();
      unsigned int get_depth_attachment();

      FramebufferData* get_data();
    };
  }
}

#endif
