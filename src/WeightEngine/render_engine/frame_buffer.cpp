#include <WeightEngine/render_engine/frame_buffer.h>

using namespace WeightEngine;
using namespace RenderEngine;

Framebuffer::Framebuffer(FramebufferData* _data):data(_data){
  rebuild();
}
Framebuffer::~Framebuffer(){
  glDeleteFramebuffers(1, &id);
}

void Framebuffer::rebuild(){
  glCreateFramebuffers(1, &id);
  bind();

  glCreateTextures(GL_TEXTURE_2D, 1, &colour_attachment);
  glBindTexture(GL_TEXTURE_2D, colour_attachment);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data->width, data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colour_attachment, 0);

  glCreateTextures(GL_TEXTURE_2D, 1, &depth_attachment);
  glBindTexture(GL_TEXTURE_2D, depth_attachment);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, data->width, data->height);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_attachment, 0);

  int status=glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(status!=GL_FRAMEBUFFER_COMPLETE){
    WEIGHT_ERROR("Framebuffer: {0} cannot be built. Error: {1}", id, status);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bind(){
  glBindFramebuffer(GL_FRAMEBUFFER, id);
}
void Framebuffer::unbind(){
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Framebuffer::get_colour_attachment(){
  return colour_attachment;
}
unsigned int Framebuffer::get_depth_attachment(){
  return depth_attachment;
}

FramebufferData* Framebuffer::get_data(){
  return data;
}
