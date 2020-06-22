#include <WeightEngine/render_engine/shaders/Light2D_shader.h>

using namespace WeightEngine;
using namespace RenderEngine;

Light2DShader* Light2DShader::instance=0;

Light2DShader* Light2DShader::get(){
  if(instance==0){
    std::unordered_map<int, std::string> arg;
    arg[GL_VERTEX_SHADER]="WeightEngineResources/shaders/Light2D_vertex.glsl";
    arg[GL_FRAGMENT_SHADER]="WeightEngineResources/shaders/Light2D_fragment.glsl";
    instance=new Light2DShader(arg);
  }
  return instance;
}

Light2DShader::Light2DShader(std::unordered_map<int, std::string> _files):Shader(_files){
  files=_files;
}

Light2DShader::~Light2DShader(){
  this->Shader::~Shader();
}
