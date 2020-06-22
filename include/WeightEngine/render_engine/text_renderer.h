#ifndef WEIGHT_ENGINE__RENDER_ENGINE__TEXT_RENDERER_H
#define WEIGHT_ENGINE__RENDER_ENGINE__TEXT_RENDERER_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/render_engine/vertex.h>
#include <WeightEngine/render_engine/font.h>
#include <WeightEngine/render_engine/shaders/text_shader.h>

#include <FreeType/FreeTypeAmalgam.h>
#if defined(WEIGHT_DESKTOP)
  #include <glad/glad.h>
#elif defined(WEIGHT_ANDROID)
  #include <EGL/egl.h>
  #include <GLES/gl.h>
#elif defined(WEIGHT_IOS)
#endif
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>
/*
Help from:
https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_01
https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_02
https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_03
https://learnopengl.com/In-Practice/Text-Rendering
 */
namespace WeightEngine{
  namespace RenderEngine{
    struct WEIGHT_API CharacterRenderData{
      WeightEngine::RenderEngine::Vertex vertices[4];
    };

    struct WEIGHT_API Text{
      int id;
      std::string text;
      WeightEngine::Position3D pos;
      WeightEngine::RenderEngine::Font* font;
      WeightEngine::Colour colour;
      float size;

      std::vector<CharacterRenderData> character_data;

      void move(WeightEngine::Position3D translation);
      void move(WeightEngine::Position2D translation);
      void set_position(WeightEngine::Position3D position);
      void set_position(WeightEngine::Position2D position);
      void set_colour(WeightEngine::Colour _colour);

      void set_size(float _size);
      int get_size();

      void rotate(float degrees);
      //void scale(float factor); //Removed because will cause interference with the set position method due to maths
    };

    class WEIGHT_API TextRenderer{
    private:
      FT_Library library;

      unsigned int vertex_array;
      unsigned int vertex_buffer;
      unsigned int index_buffer;
      int samplers[MAX_TEXTURES];
      int max_chars;
      int max_vertex;
      int max_index;
      int number_chars;
      std::vector<Text*> geometry;

      int id_number; //To store id number we are up to for the text objects
    public:
      TextRenderer(int _max_chars);
      ~TextRenderer();

      void submit(Text* text);
      void remove(Text* text);
      void render(glm::mat4 mvp, float ts);

      WeightEngine::RenderEngine::Font* load_font(std::string path);
      Text* generate_text(std::string text, WeightEngine::Position2D pos, WeightEngine::RenderEngine::Font* font, WeightEngine::Colour colour, float size, bool affect_mvp=true); //Pos being top left of start
      Text* generate_text(std::string text, WeightEngine::Position3D pos, WeightEngine::RenderEngine::Font* font, WeightEngine::Colour colour, float size, bool affect_mvp=true);
    };
  }
}

#endif
