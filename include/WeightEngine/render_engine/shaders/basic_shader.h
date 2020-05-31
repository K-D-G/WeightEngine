#ifndef WEIGHT_ENGINE__RENDER_ENGINE__BASIC_SHADER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__BASIC_SHADER_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/render_engine/shader.h>

#include <string>
#include <unordered_map>

namespace Weight{
  namespace RenderEngine{
    //Using a singleton because this shouldn't be duplicated as the renderer creates it
    //automatically as it does basic stuff
    class WEIGHT_API BasicShader:public Shader{
    private:
      static BasicShader* instance;
      BasicShader(std::unordered_map<int, std::string> _files);
      BasicShader(const BasicShader&)=delete;
      BasicShader& operator=(const BasicShader&)=delete;
    public:
      ~BasicShader();
      std::unordered_map<int, std::string> files;

      static BasicShader* get();
    };
  }
}
#endif
