#ifndef WEIGHT_ENGINE__RENDER_ENGINE__SHADER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__SHADER_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace Weight{
  namespace RenderEngine{
    class WEIGHT_API Shader{
    private:
      int _id;
      std::unordered_map<int, std::string> _shaders;
      std::unordered_map<std::string, int> _uniforms;

      static int load_shader(std::string path, int type);
      int get_uniform_location(std::string name);
    public:
      Shader(std::unordered_map<int, std::string> _files); //Map of types->paths
      ~Shader();

      void bind();
      void unbind();

      //Uniform functions
      void set_float(std::string name, float value);
      void set_vector(std::string name, glm::vec3 vector);
      void set_vector2(std::string name, glm::vec2 vector);
      void set_boolean(std::string name, bool value);
      void set_matrix(std::string name, glm::mat4 matrix);
      void set_int_array(std::string name, int* values, int count);
    };
  }
}


#endif
