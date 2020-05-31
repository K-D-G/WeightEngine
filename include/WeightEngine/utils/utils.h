#ifndef WEIGHT_ENGINE__UTILS__UTILS_H
#define WEIGHT_ENGINE__UTILS__UTILS_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include <string>
#include <unordered_map>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <cmath>

#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/maths_utils.h>

#include <glad/glad.h>

namespace Weight{
  struct WEIGHT_API Vector2D{
    float x, y;
  };
  struct WEIGHT_API Vector3D{
    float x, y, z;
  };

  struct WEIGHT_API Position2D{
    float x, y;
  };
  struct WEIGHT_API Position3D{
    float x, y, z;
  };
  struct WEIGHT_API Colour{
    float r, g, b, a;
  };

  inline bool operator==(const Position3D& lhs, const Position3D& rhs){
    return (lhs.x==rhs.x&&lhs.y==rhs.y&&lhs.z==rhs.z);
  }

  inline bool operator==(const Vector3D& lhs, const Vector3D& rhs){
    return (lhs.x==rhs.x&&lhs.y==rhs.y&&lhs.z==rhs.z);
  }

  inline bool operator==(const Position2D& lhs, const Position2D& rhs){
    return (lhs.x==rhs.x&&lhs.y==rhs.y);
  }

  inline bool operator==(const Vector2D& lhs, const Vector2D& rhs){
    return (lhs.x==rhs.x&&lhs.y==rhs.y);
  }

  inline bool operator==(const Colour& lhs, const Colour& rhs){
    return (lhs.r==rhs.r&&lhs.g==rhs.g&&lhs.b==rhs.b&&lhs.a==rhs.a);
  }

  inline bool operator!=(const Position3D& lhs, const Position3D& rhs){
    return (lhs.x!=rhs.x&&lhs.y!=rhs.y&&lhs.z!=rhs.z);
  }

  inline bool operator!=(const Vector3D& lhs, const Vector3D& rhs){
    return (lhs.x!=rhs.x&&lhs.y!=rhs.y&&lhs.z!=rhs.z);
  }

  inline bool operator!=(const Position2D& lhs, const Position2D& rhs){
    return (lhs.x!=rhs.x&&lhs.y!=rhs.y);
  }

  inline bool operator!=(const Vector2D& lhs, const Vector2D& rhs){
    return (lhs.x!=rhs.x&&lhs.y!=rhs.y);
  }

  inline bool operator!=(const Colour& lhs, const Colour& rhs){
    return (lhs.r!=rhs.r&&lhs.g!=rhs.g&&lhs.b!=rhs.b&&lhs.a!=rhs.a);
  }

  inline bool operator==(const Position3D& lhs, const Position3D* rhs){
    if(rhs==nullptr||rhs==NULL){
      return (lhs.x&&lhs.y&&lhs.z);
    }
    return false;
  }

  inline bool operator==(const Vector3D& lhs, const Vector3D* rhs){
    if(rhs==nullptr||rhs==NULL){
      return (lhs.x&&lhs.y&&lhs.z);
    }
    return false;
  }

  inline bool operator==(const Position2D& lhs, const Position2D* rhs){
    if(rhs==nullptr||rhs==NULL){
      return (lhs.x&&lhs.y);
    }
    return false;
  }

  inline bool operator==(const Vector2D& lhs, const Vector2D* rhs){
    if(rhs==nullptr||rhs==NULL){
      return (lhs.x&&lhs.y);
    }
    return false;
  }

  inline bool operator!=(const Colour& lhs, const Colour* rhs){
    if(rhs==nullptr||rhs==NULL){
      return (lhs.r&&lhs.g&&lhs.b&&lhs.a);
    }
    return false;
  }

  class WEIGHT_API COLOURS{
  public:
    static Colour RED;
    static Colour GREEN;
    static Colour BLUE;
    static Colour BLACK;
    static Colour WHITE;
    static Colour YELLOW;
    static Colour PURPLE;
    static Colour BROWN;
    static Colour ORANGE;
    static Colour GREY;
    static Colour PINK;
  };

  class WEIGHT_API Utils{
  public:
    struct Image{
      std::string path;
      int width, height, bpp;
      unsigned char* buffer;
    };
    static Colour create_colour(int r, int g, int b, int a);
    static Position2D create_position(float x, float y);
    static Position3D create_position(float x, float y, float z);
    static glm::mat4 create_projection_matrix(float left, float right, float bottom, float top);

    static std::unordered_map<std::string, unsigned int> textures_loaded;
    static unsigned int blank_texture_id;

    static Utils::Image* load_image(std::string path);
    static void free_image_buffer(Utils::Image* image);
    static unsigned int load_opengl_texture(Utils::Image* image);
    static unsigned int load_opengl_texture(std::string name, int width, int height, unsigned char* buffer);
    static void delete_opengl_texture(unsigned int id);
    static void delete_opengl_texture(std::string name);
    static unsigned int load_blank_opengl_texture();

    static std::string load_file(std::string path);
    static void write_file(std::string path, std::string data);
    static float timestamp_to_number(std::string timestamp);

    static float distance(Weight::Position2D v1, Weight::Position2D v2);
    static float distance(Weight::Position3D v1, Weight::Position3D v2);
    static float distance(Weight::Position3D v1, Weight::Position2D v2);
    static float distance(Weight::Position2D v1, Weight::Position3D v2);

    #if defined(WEIGHT_DEBUG) && !defined(__APPLE__)
    static void GLAPIENTRY opengl_error_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param);
    #endif
  };
}
#endif
