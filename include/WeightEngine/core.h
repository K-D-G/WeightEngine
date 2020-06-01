#ifndef WEIGHT_ENGINE__CORE_H
#define WEIGHT_ENGINE__CORE_H

#define WEIGHT_DEBUG

#if defined(WIN32)||defined(_WIN32)||defined(__WIN32__)||defined(__NT__)
  //#define WEIGHT_USE_GLFW
  #define WEIGHT_DESKTOP
  #define WEIGHT_SETUP using Application::Application
  #ifdef WEIGHT_BUILD
    #define WEIGHT_API __declspec(dllexport)
  #else
    #define WEIGHT_API __declspec(dllimport)
  #endif
#elif defined(__APPLE__)
  #include <TargetConditionals.h>
  #if defined(TARGET_OS_MAC)
    //#define WEIGHT_USE_GLFW
    #define WEIGHT_DESKTOP
    #define WEIGHT_SETUP using Application::Application
  #elif defined(TARGET_OS_IOS)
    #define WEIGHT_MOBILE
    #define WEIGHT_IOS
  #endif
#elif defined(__linux__)
  #if !defined(__ANDROID__)
    //#define WEIGHT_USE_GLFW
    #define WEIGHT_DESKTOP
    #define WEIGHT_SETUP using Application::Application
  #else
    #define WEIGHT_MOBILE
    #define WEIGHT_ANDROID
  #endif
#endif

#ifndef WEIGHT_API
  #define WEIGHT_API
#endif

#include <glad/glad.h>
#define MAX_TEXTURES GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
#define MAX_PARTICLES 10000
#define MAX_QUADS 100000
#define MAX_CHARS 10000
#define MAX_WIDGETS 10000
#define MAX_LIGHTS 100000
#define NUMBER_FONT_CHARS 256

//Macros
#define CHECK_BIT(val, pos) ((val)&(1<<(pos)))

#endif
