#ifndef WEIGHT_ENGINE__RENDER_ENGINE__PARTICLE2D_SHADER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__PARTICLE2D_SHADER_H
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
    class WEIGHT_API Particle2DShader:public Shader{
    private:
      static Particle2DShader* instance;
      Particle2DShader(std::unordered_map<int, std::string> _files);
      Particle2DShader(const Particle2DShader&)=delete;
      Particle2DShader& operator=(const Particle2DShader&)=delete;
    public:
      ~Particle2DShader();
      std::unordered_map<int, std::string> files;

      static Particle2DShader* get();
    };
  }
}

#endif
