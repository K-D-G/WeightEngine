#ifndef WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_ANIMATION_H
#define WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_ANIMATION_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/time.h>
#include <WeightEngine/render_engine/texture_atlas.h>

#include <json.h>

#include <string>

using json=nlohmann::json;

namespace Weight{
  namespace RenderEngine{
    class WEIGHT_API Animation2D{
    private:
      Weight::RenderEngine::TextureAtlas* texture_atlas;
      json animation_data;

      //For current animation
      bool play;
      bool loop;
      int frame_number;
      int frame_count;
      int start_tile;
      std::string current_animation;

      float frame_step; //Time between showing each frame
      float time_accumulation; //Tracking time so we know when to show each frame
    public:
      Animation2D(std::string texture_path, std::string details_path);
      ~Animation2D();

      void reload_animations(std::string texture_path, std::string details_path);
      void play_animation(std::string name, int frame_start=0, bool _loop=false);
      void stop_animation();

      Weight::RenderEngine::SubTexture* update();

    };
  }
}

#endif
