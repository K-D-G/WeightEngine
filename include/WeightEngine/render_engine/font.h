#ifndef WEIGHT_ENGINE__RENDER_ENGINE__FONT_H
#define WEIGHT_ENGINE__RENDER_ENGINE__FONT_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>

#include <FreeType/FreeTypeAmalgam.h>
#include <glad/glad.h>
#include <string>
#include <vector>
#include <algorithm>

//We are basically texture atlasing here but not using the class because the
//texture atlas class needs fixed sized textures which we don't have here because
//fonts
namespace WeightEngine{
  namespace RenderEngine{
    struct WEIGHT_API Character{
      float offset; //x offset in texture coords
      WeightEngine::Vector2D size;
      WeightEngine::Vector2D bearing;
      WeightEngine::Vector2D advance;
    };

    class WEIGHT_API Font{
    private:
      std::string path;

      FT_Face face;
      FT_Library& library;

      unsigned int texture_id;
      int number_characters;

      WeightEngine::Vector2D atlas_dimensions;
    public:
      std::vector<Character> characters;

      Font(std::string font_path, int num_characters, FT_Library& lib);
      ~Font();

      void reload_font(std::string font_path);

      std::string get_font_path();
      unsigned int get_texture_id();

      WeightEngine::Vector2D get_atlas_dimensions();
    };
  }
}

#endif
