#include <WeightEngine/utils/utils.h>

using namespace WeightEngine;

Colour COLOURS::RED={1.0f, 0.0f, 0.0f, 1.0f};
Colour COLOURS::GREEN={0.0f, 1.0f, 0.0f, 1.0f};
Colour COLOURS::BLUE={0.0f, 0.0f, 1.0f, 1.0f};
Colour COLOURS::BLACK={0.0f, 0.0f, 0.0f, 1.0f};
Colour COLOURS::WHITE={1.0f, 1.0f, 1.0f, 1.0f};
Colour COLOURS::YELLOW={1.0f, 1.0f, 0.0f, 1.0f};
Colour COLOURS::PURPLE={0.41568627450980394, 0.050980392156862744, 0.6784313725490196, 1};
Colour COLOURS::BROWN={0.5882352941176471, 0.29411764705882354, 0, 1};
Colour COLOURS::ORANGE={0.39215686274509803, 0.2549019607843137, 0, 1};
Colour COLOURS::GREY={0.19607843137254902, 0.19607843137254902, 0.19607843137254902, 1};
Colour COLOURS::PINK={1, 0.7529411764705882, 0.796078431372549, 1};

std::unordered_map<std::string, unsigned int> Utils::textures_loaded;
unsigned int Utils::blank_texture_id;

Colour Utils::create_colour(int r, int g, int b, int a){
  return {Maths::map((float)r, 0.0f, 255.0f, 0.0f, 1.0f, true), Maths::map((float)g, 0.0f, 255.0f, 0.0f, 1.0f, true), Maths::map((float)b, 0.0f, 255.0f, 0.0f, 1.0f, true), Maths::map((float)a, 0.0f, 255.0f, 0.0f, 1.0f, true)};
}

Position2D Utils::create_position(float x, float y){
  return {x, y};
}

Position3D Utils::create_position(float x, float y, float z){
  return {x, y, z};
}

glm::mat4 Utils::create_projection_matrix(float left, float right, float bottom, float top){
  return glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}

Utils::Image* Utils::load_image(std::string path){
  Utils::Image* result=new Utils::Image;
  result->path=path;
  stbi_set_flip_vertically_on_load(1);
  result->buffer=stbi_load(path.c_str(), &result->width, &result->height, &result->bpp, 4);
  if(!result->buffer){
    WEIGHT_WARNING("Image: ({0}) doesn't contain any data", path);
    if(stbi_failure_reason()){
      WEIGHT_ERROR("STB image loading failed because: {0}", stbi_failure_reason());
    }else{
      WEIGHT_ERROR("STB image gives no reason for failure");
    }
  }
  return result;
}

void Utils::free_image_buffer(Utils::Image* image){
  if(image->buffer){
    stbi_image_free(image->buffer);
  }
}

unsigned int Utils::load_opengl_texture(Utils::Image* image){
  if(Utils::textures_loaded[image->path]){
    return Utils::textures_loaded[image->path];
  }

  unsigned int id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->buffer);

  Utils::textures_loaded[image->path]=id;
  Utils::free_image_buffer(image);
  return id;
}

unsigned int Utils::load_opengl_texture(std::string name, int width, int height, unsigned char* buffer){
  if(Utils::textures_loaded[name]){
    return Utils::textures_loaded[name];
  }
  unsigned int id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

  Utils::textures_loaded[name]=id;
  return id;
}

void Utils::delete_opengl_texture(unsigned int id){
  glDeleteTextures(1, &id);
  for(std::unordered_map<std::string, unsigned int>::const_iterator it=Utils::textures_loaded.begin(); it!=Utils::textures_loaded.end(); ++it) {
    if(it->second==id){
      Utils::textures_loaded.erase(it->first);
    }
  }
}

void Utils::delete_opengl_texture(std::string name){
  glDeleteTextures(1, &Utils::textures_loaded[name]);
  Utils::textures_loaded.erase(name);
}

unsigned int Utils::load_blank_opengl_texture(){
  if(Utils::blank_texture_id){
    return Utils::blank_texture_id;
  }
  unsigned int result;
  unsigned char* pixels=new unsigned char[256*256*4];
  for(int i=0; i<256*256*4; i++){
    pixels[i]=255;
  }
  glGenTextures(1, &result);
  glBindTexture(GL_TEXTURE_2D, result);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  delete[] pixels;
  Utils::blank_texture_id=result;
  return result;
}

std::string Utils::load_file(std::string path){
  std::ifstream t(path);
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  return str;
}

void Utils::write_file(std::string path, std::string data){
  std::ofstream out(path);
  out<<data;
  out.close();
}

float Utils::timestamp_to_number(std::string timestamp){
  int colon=timestamp.find(":");
  if(colon==std::string::npos){
    WEIGHT_ERROR("Timestamp formated incorrectly, should be formated as 00:00");
    return -1.0f;
  }
  int colon2=timestamp.find(":", colon+1);
  float result;
  if(colon2!=std::string::npos){
    //Hours
    int hours=std::stoi(timestamp.substr(0, 2), nullptr);
    int minutes=std::stoi(timestamp.substr(colon+1, 2), nullptr);
    int seconds=std::stoi(timestamp.substr(colon2+1, 2), nullptr);

    result=((float)hours*60*60)+((float)minutes*60)+((float)seconds);
  }else{
    //No hours
    int minutes=std::stoi(timestamp.substr(0, 2), nullptr);
    int seconds=std::stoi(timestamp.substr(colon+1, 2), nullptr);

    result=((float)minutes*60)+((float)seconds);
  }
  return result;
}

float Utils::distance(Position2D v1, Position2D v2){
  return sqrt(pow(v1.x-v2.x, 2)+pow(v1.y-v2.y, 2));
}
float Utils::distance(Position3D v1, Position3D v2){
  return sqrt(pow(v1.x-v2.x, 2)+pow(v1.y-v2.y, 2));
}
float Utils::distance(Position2D v1, Position3D v2){
  return sqrt(pow(v1.x-v2.x, 2)+pow(v1.y-v2.y, 2));
}
float Utils::distance(Position3D v1, Position2D v2){
  return sqrt(pow(v1.x-v2.x, 2)+pow(v1.y-v2.y, 2));
}

#if defined(WEIGHT_DEBUG) && !defined(__APPLE__)
void GLAPIENTRY Utils::opengl_error_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param){
  char* x;
  sprintf(x, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type==GL_DEBUG_TYPE_ERROR?"** GL ERROR **":""), type, severity, message);
  WEIGHT_ERROR("OpenGL error: {0}", x);
}
#endif
