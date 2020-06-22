#ifndef WEIGHT_ENGINE__RENDER_ENGINE__SCENE_MANAGER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__SCENE_MANAGER_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/render_engine/scene.h>

#include <string>
#include <map>

namespace WeightEngine{
  namespace RenderEngine{
    class WEIGHT_API SceneManager{
    public:
      std::map<std::string, WeightEngine::RenderEngine::Scene*> scenes;
      std::string current_scene;
    public:
      SceneManager();
      ~SceneManager();

      void load_scene(std::string path);
      void switch_scene(std::string scene);
    };
  }
}
#endif
