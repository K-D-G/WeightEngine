#include <WeightEngine/render_engine/scene_manager.h>

using namespace Weight;
using namespace RenderEngine;

SceneManager::SceneManager(){

}
SceneManager::~SceneManager(){

}

void SceneManager::load_scene(std::string path){
  Scene* s=new Scene(path);
  scenes[s->get_name()]=s;
}
void SceneManager::switch_scene(std::string scene){
  if(scenes.find(scene)!=scenes.end()){
    WEIGHT_ERROR("SceneManager: Trying to switch to a scene which doesn't exist ({0})", scene);
    return;
  }

  scenes[current_scene]->destroy();
  current_scene=scene;
  scenes[current_scene]->setup();
}
