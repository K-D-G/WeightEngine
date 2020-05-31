#ifndef WEIGHT_ENGINE__RENDER_ENGINE__SCENE_H
#define WEIGHT_ENGINE__RENDER_ENGINE__SCENE_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>

#include <json.h>

#include <string>
#include <vector>

using json=nlohmann::json;

namespace Weight{
  namespace RenderEngine{
    class WEIGHT_API Scene{
    private:
      std::string name;
      json data;
    public:
      Scene(std::string path);
      ~Scene();

      void setup();
      void destroy();

      std::string get_name();
    };
  }
}

#endif
