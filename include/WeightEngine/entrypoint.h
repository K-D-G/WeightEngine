#ifndef WEIGHT_ENGINE__ENTRYPOINT_H
#define WEIGHT_ENGINE__ENTRYPOINT_H
#include <WeightEngine/core.h>
#include <WeightEngine/Application.h>

#if defined(WEIGHT_DESKTOP)

namespace Weight{
  extern Weight::Application* create_application();
}

int main(){
  Weight::Application* app=Weight::create_application();
  app->run();
  delete app;
  return 0;
}

#elif defined(WEIGHT_ANDROID)
#include <memory>
#include <jni.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android_native_app_glue.h>

struct savedstate{

};

struct weight_state{
  android_app* app;

  EGLDisplay display;
  EGLSurface surface;
  EGLContext context;
  int width;
  int height;

  savedstate saved_state;
};

void android_main(android_app* state){
  weight_state weight_engine;
  memset(&weight_engine, 0, sizeof(weight_state));
  state->userData=&weight_engine;
  state->onInputEvent=; //Write this in event_system

  //Get access to the sensors here

  if(state->savedState!=nullptr){
    weight_engine.state=*(savedstate*)state->savedState;
  }
  //Setup stuff with window in the window class etc
  //Setup the sensors and events etc
  //Do stuff with the saved_state
  Weight::Application* app=Weight::create_application();
  app->run();
  delete app;
}

#elif defined(WEIGHT_IOS)

#endif

#endif
