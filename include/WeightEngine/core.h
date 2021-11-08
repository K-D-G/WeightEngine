#ifndef WEIGHT_ENGINE__CORE_H
#define WEIGHT_ENGINE__CORE_H

#if defined(WIN32)||defined(_WIN32)||defined(__WIN32__)||defined(__NT__)
  #define WEIGHT_DESKTOP
  #define WEIGHT_WINDOWS
  #ifdef WEIGHT_BUILD
    #define WEIGHT_API __declspec(dllexport)
  #else
    #define WEIGHT_API __declspec(dllimport)
  #endif
#elif defined(__APPLE__)
  #include <TargetConditionals.h>
  #if defined(TARGET_OS_MAC)
    #define WEIGHT_DESKTOP
    #define WEIGHT_MAC
  #elif defined(TARGET_OS_IOS)
    #define WEIGHT_MOBILE
    #define WEIGHT_IOS
  #endif
#elif defined(__linux__)
  #if !defined(__ANDROID__)
    #define WEIGHT_DESKTOP
    #define WEIGHT_LINUX
  #else
    #define WEIGHT_MOBILE
    #define WEIGHT_ANDROID
  #endif
#endif

#ifndef WEIGHT_API
  #define WEIGHT_API
#endif

#define WEIGHT_SETUP using Application::Application

#if defined(WEIGHT_DESKTOP)
  #include <glad/glad.h>
#elif defined(WEIGHT_ANDROID)
  #include <EGL/egl.h>
  #include <GLES/gl.h>
#elif defined(WEIGHT_IOS)
#endif
#define MAX_TEXTURES GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS

#define X_AXIS 1
#define Y_AXIS 2

#if defined(WEIGHT_DESKTOP)
#define MAX_PARTICLES 10000
#define MAX_QUADS 100000
#define MAX_CHARS 10000
#define MAX_WIDGETS 10000
#define MAX_LIGHTS 100000
#define NUMBER_FONT_CHARS 256
#define PHYSICS_VELOCITY_ITERATIONS 8
#define PHYSICS_POSITION_ITERATIONS 3
#elif defined(WEIGHT_MOBILE)
#define MAX_PARTICLES 5000
#define MAX_QUADS 50000
#define MAX_CHARS 5000
#define MAX_WIDGETS 5000
#define MAX_LIGHTS 50000
#define NUMBER_FONT_CHARS 256
#define PHYSICS_VELOCITY_ITERATIONS 6
#define PHYSICS_POSITION_ITERATIONS 2
#endif

//Macros
#define CHECK_BIT(val, pos) ((val)&(1<<(pos)))

#endif
