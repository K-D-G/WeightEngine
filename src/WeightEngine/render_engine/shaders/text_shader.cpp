#include <WeightEngine/render_engine/shaders/text_shader.h>

using namespace Weight;
using namespace RenderEngine;

TextShader* TextShader::instance=0;

TextShader* TextShader::get(){
  if(instance==0){
    std::unordered_map<int, std::string> arg;
    arg[GL_VERTEX_SHADER]="WeightEngineResources/shaders/text_vertex.glsl";
    arg[GL_FRAGMENT_SHADER]="WeightEngineResources/shaders/text_fragment.glsl";
    instance=new TextShader(arg);
  }
  return instance;
}

TextShader::TextShader(std::unordered_map<int, std::string> _files):Shader(_files){
  files=_files;
}

TextShader::~TextShader(){
  this->Shader::~Shader();
}
