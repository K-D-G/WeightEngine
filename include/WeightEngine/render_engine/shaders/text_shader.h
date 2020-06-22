#ifndef WEIGHT_ENGINE__RENDER_ENGINE__TEXT_SHADER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__TEXT_SHADER_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/render_engine/shader.h>

#include <string>
#include <unordered_map>

namespace WeightEngine{
  namespace RenderEngine{
    //Using a singleton because this shouldn't be duplicated as the renderer creates it
    //automatically as it does basic stuff
    class WEIGHT_API TextShader:public Shader{
    private:
      static TextShader* instance;
      TextShader(std::unordered_map<int, std::string> _files);
      TextShader(const TextShader&)=delete;
      TextShader& operator=(const TextShader&)=delete;
    public:
      ~TextShader();
      std::unordered_map<int, std::string> files;

      static TextShader* get();
    };
  }
}
#endif
