#include <WeightEngine/render_engine/shaders/basic_shader.h>

using namespace WeightEngine;
using namespace RenderEngine;

BasicShader* BasicShader::instance=0;

BasicShader* BasicShader::get(){
  if(instance==0){
    std::unordered_map<int, std::string> arg;
    arg[GL_VERTEX_SHADER]="WeightEngineResources/shaders/basic_vertex.glsl";
    arg[GL_FRAGMENT_SHADER]="WeightEngineResources/shaders/basic_fragment.glsl";
    instance=new BasicShader(arg);
  }
  return instance;
}

BasicShader::BasicShader(std::unordered_map<int, std::string> _files):Shader(_files){
  files=_files;
}

BasicShader::~BasicShader(){
  this->Shader::~Shader();
}
