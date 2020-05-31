#ifndef WEIGHT_ENGINE__RENDER_ENGINE__ORTHOGRAPHIC_CAMERA_H
#define WEIGHT_ENGINE__RENDER_ENGINE__ORTHOGRAPHIC_CAMERA_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/maths_utils.h>
#include <WeightEngine/utils/utils.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace Weight{
  namespace RenderEngine{
    class WEIGHT_API OrthographicCamera{
    private:
      glm::mat4 projection_matrix;
      glm::mat4 view_matrix;

      glm::mat4 view_projection_matrix;

      glm::vec3 position=glm::vec3(0.0f, 0.0f, 0.0f);
      float rotation=0.0f;

      void recalculate_view_matrix();

      int* screen_width;
      int* screen_height;
    public:
      OrthographicCamera(float left, float right, float bottom, float top, int* _screen_width, int* _screen_height);
      ~OrthographicCamera();

      void set_position(glm::vec3 pos);
      void set_rotation(float rot);

      glm::vec3 get_position();
      float get_rotation();

      glm::mat4 get_projection_matrix();
      glm::mat4 get_view_matrix();
      glm::mat4 get_view_projection_matrix();

      void set_projection(float left, float right, float bottom, float top);
    };
  }
}
#endif
