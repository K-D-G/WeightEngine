#ifndef WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_H
#define WEIGHT_ENGINE__RENDER_ENGINE__2D__2D_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/utils.h>
#include <WeightEngine/utils/maths_utils.h>
#include <WeightEngine/render_engine/shader.h>
#include <WeightEngine/render_engine/shaders/basic_shader.h>
#include <WeightEngine/render_engine/texture_atlas.h>
#include <WeightEngine/render_engine/vertex.h>

#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

#include <cstdlib>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Weight{
  namespace RenderEngine{
    #define X_AXIS 1
    #define Y_AXIS 2

    struct WEIGHT_API QuadData{
      int id;
      unsigned int texture_id;
      Weight::Vector2D dimensions;
      Weight::RenderEngine::Vertex vertices[4];
      //Weight::Position3D centre_pos;

      void move(Weight::Position3D translation);
      void move(Weight::Position2D translation);
      void set_position(Weight::Position3D position);
      void set_position(Weight::Position2D position);
      void set_size(float width, float height);

      void rotate(float degrees);
      void flip(int axis);
      void scale(float factor);

      void set_texture(std::string path);
      void set_texture_from_atlas(Weight::RenderEngine::SubTexture* texture);

      void fill(Weight::Colour colour);
      inline void no_fill(){fill({0.0f, 0.0f, 0.0f, 0.0f});}
    };

    class WEIGHT_API Renderer2D{
    private:
      unsigned int vertex_array;
      unsigned int vertex_buffer;
      unsigned int index_buffer;
      int samplers[MAX_TEXTURES];
      int max_quad;
      int max_vertex;
      int max_index;
      QuadData* background;
      bool do_render_background;
      std::vector<QuadData*> geometry;

      int id_number; //To store the id we are up to for the quads doesn't need to be a secure variable
      int blank_texture_id; //For colour quads
    public:
      Renderer2D(int _max_quad);
      ~Renderer2D();

      QuadData* create_quad(Weight::Position2D position, float width, float height, Weight::Colour colour, bool affect_mvp=true);
      QuadData* create_quad(Weight::Position2D position, float width, float height, std::string texture_path, bool affect_mvp=true);

      QuadData* create_quad(Weight::Position3D position, float width, float height, Weight::Colour colour, bool affect_mvp=true);
      QuadData* create_quad(Weight::Position3D position, float width, float height, std::string texture_path, bool affect_mvp=true);

      void submit(QuadData* q);
      void remove(QuadData* q);
      void render(glm::mat4 mvp, float ts);

      void set_background_image(std::string background_path);
      void render_background(glm::mat4 mvp);
    };
  }
}

#endif
