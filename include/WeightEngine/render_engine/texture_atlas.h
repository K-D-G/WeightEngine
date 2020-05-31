#ifndef WEIGHT_ENGINE__RENDER_ENGINE__TEXTURE_ATLAS_H
#define WEIGHT_ENGINE__RENDER_ENGINE__TEXTURE_ATLAS_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>

#include <string>
#include <vector>

namespace Weight{
  namespace RenderEngine{
    struct WEIGHT_API SubTexture{
      unsigned int texture_id;
      float texture_coords[8];

      int x, y;
    };
    class WEIGHT_API TextureAtlas{
    private:
      std::string path;
      unsigned int texture_id;
      std::vector<SubTexture*> generated_coords;
    public:
      int image_width;
      int image_height;

      int text_width;
      int text_height;

      int textures_wide;
      int textures_tall;
      int number_textures;

      TextureAtlas(std::string texture_path, int texture_width, int texture_height);
      TextureAtlas(std::string name, int width, int height, int texture_width, int texture_height, unsigned char* buffer);
      ~TextureAtlas();

      std::string get_path();
      unsigned int get_texture_id();
      void reload_texture(std::string texture_path, int texture_width, int texture_height);
      void reload_texture(std::string name, int width, int height, int texture_width, int texture_height, unsigned char* buffer);

      SubTexture* get_texture(int x, int y); //From bottom left of the texture
    };
  }
}

#endif
