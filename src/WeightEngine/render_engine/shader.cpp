#include <WeightEngine/render_engine/shader.h>

using namespace Weight;
using namespace RenderEngine;


Shader::Shader(std::unordered_map<int, std::string> _files){
  _id=glCreateProgram();
  _shaders=_files;
  for(std::unordered_map<int, std::string>::iterator it=_shaders.begin(); it!=_shaders.end(); it++){
    glAttachShader(_id, Shader::load_shader(it->second, it->first));
  }
  glLinkProgram(_id);
  #ifdef WEIGHT_DEBUG
  int link_status;
  glGetProgramiv(_id, GL_LINK_STATUS, &link_status);
  if(link_status==GL_FALSE){
    int length;
    glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);
    char* error=(char*)alloca(length*sizeof(char));
    glGetProgramInfoLog(_id, length, &length, error);
    WEIGHT_ERROR("OpenGL couldn't link shader: {0}", error);
    glDeleteProgram(_id);
  }
  #endif
  glValidateProgram(_id);

  #ifdef WEIGHT_DEBUG
  int validate_status;
  glGetProgramiv(_id, GL_VALIDATE_STATUS, &validate_status);
  if(validate_status==GL_FALSE){
    int length;
    glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);
    char* error=(char*)alloca(length*sizeof(char));
    glGetProgramInfoLog(_id, length, &length, error);
    WEIGHT_ERROR("OpenGL couldn't validate shader: {0}", error);
    glDeleteProgram(_id);
  }
  #endif
  WEIGHT_SUCCESS("Shader created");
}

Shader::~Shader(){
  WEIGHT_LOG("Shader (containing: {0}) destructing", _shaders.begin()->second);
  unbind();
  for(std::unordered_map<int, std::string>::iterator it=_shaders.begin(); it!=_shaders.end(); it++){
    glDetachShader(_id, it->first);
    glDeleteShader(_id);
  }
  glDeleteProgram(_id);
}

void Shader::bind(){
  glUseProgram(_id);
}

void Shader::unbind(){
  glUseProgram(0);
}

int Shader::get_uniform_location(std::string name){
  std::unordered_map<std::string, int>::iterator it=_uniforms.find(name);
  if(it!=_uniforms.end()){
    return it->second;
  }
  _uniforms[name]=glGetUniformLocation(_id, name.c_str());
  return _uniforms[name];
}

void Shader::set_float(std::string name, float value){
  glUniform1f(get_uniform_location(name), value);
}
void Shader::set_vector(std::string name, glm::vec3 vector){
  glUniform3f(get_uniform_location(name), vector.x, vector.y, vector.z);
}

void Shader::set_vector2(std::string name, glm::vec2 vector){
  glUniform2f(get_uniform_location(name), vector.x, vector.y);
}

void Shader::set_boolean(std::string name, bool value){
  glUniform1f(get_uniform_location(name), (value==1));
}
void Shader::set_matrix(std::string name, glm::mat4 matrix){
  glUniformMatrix4fv(get_uniform_location(name), 1, false, glm::value_ptr(matrix));
}
void Shader::set_int_array(std::string name, int* values, int count){
  glUniform1iv(get_uniform_location(name), count, values);
}


int Shader::load_shader(std::string path, int type){
  std::ifstream _reader(path);
  std::string _source((std::istreambuf_iterator<char>(_reader)), (std::istreambuf_iterator<char>()));
  const char* _src=_source.c_str();
  int id=glCreateShader(type);
  glShaderSource(id, 1, &_src, nullptr);
  glCompileShader(id);

  #ifdef WEIGHT_DEBUG
  int compile_status;
  glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
  if(compile_status==GL_FALSE){
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* error=(char*)alloca(length*sizeof(char));
    glGetShaderInfoLog(id, length, &length, error);
    WEIGHT_ERROR("OpenGL couldn't compile shader ({0}): {1}", path, error);
    glDeleteShader(id);
    return -1;
  }
  #endif
  WEIGHT_SUCCESS("Shader ({0}) compilation successful", path);
  return id;
}
