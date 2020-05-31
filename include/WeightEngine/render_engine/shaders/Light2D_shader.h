#ifndef WEIGHT_ENGINE__RENDER_ENGINE__LIGHT2D_SHADER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__LIGHT2D_SHADER_H
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
    class WEIGHT_API Light2DShader:public Shader{
    private:
      static Light2DShader* instance;
      Light2DShader(std::unordered_map<int, std::string> _files);
      Light2DShader(const Light2DShader&)=delete;
      Light2DShader& operator=(const Light2DShader&)=delete;
    public:
      ~Light2DShader();
      std::unordered_map<int, std::string> files;

      static Light2DShader* get();
    };
  }
}

#endif
