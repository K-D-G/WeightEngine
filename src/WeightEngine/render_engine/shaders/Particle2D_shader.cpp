#include <WeightEngine/render_engine/shaders/Particle2D_shader.h>

using namespace Weight;
using namespace RenderEngine;

Particle2DShader* Particle2DShader::instance=0;

Particle2DShader* Particle2DShader::get(){
  if(instance==0){
    std::unordered_map<int, std::string> arg;
    arg[GL_VERTEX_SHADER]="WeightEngineResources/shaders/Particle2D_vertex.glsl";
    //arg[GL_GEOMETRY_SHADER]="WeightEngineResources/shaders/Particle2D_geometry.glsl";
    arg[GL_FRAGMENT_SHADER]="WeightEngineResources/shaders/Particle2D_fragment.glsl";
    instance=new Particle2DShader(arg);
  }
  return instance;
}

Particle2DShader::Particle2DShader(std::unordered_map<int, std::string> _files):Shader(_files){
  files=_files;
}

Particle2DShader::~Particle2DShader(){
  this->Shader::~Shader();
}
