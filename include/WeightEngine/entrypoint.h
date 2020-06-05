#ifndef WEIGHT_ENGINE__ENTRYPOINT_H
#define WEIGHT_ENGINE__ENTRYPOINT_H
#include <WeightEngine/core.h>
#include <WeightEngine/Application.h>

namespace Weight{
  extern Weight::Application* create_application();
}

#if defined(WEIGHT_DESKTOP)

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

#include <WeightEngine/android_wrappers/android_native_app_glue.h>
#include <WeightEngine/android_wrappers/android_structs.h>

void android_main(android_app* state){
  Weight::Android::WeightState weight_engine;
  memset(&weight_engine, 0, sizeof(WeightState));
  Weight::Android::WeightState* weight_engine_pointer=new Weight::Android::WeightState(weight_engine);
  weight_engine_pointer->app=state;
  weight_engine_pointer->app->userData=weight_engine_pointer;

  //Get access to the sensors here

  if(weight_engine_pointer->app->savedState!=nullptr){
    weight_engine_pointer->state=*(Weight::Android::SavedState*)weight_engine_pointer->app->savedState;
  }
  //Setup stuff with window in the window class etc
  //Setup the sensors and events etc
  //Do stuff with the saved_state
  //Don't forget to update core with the max textures
  //Get from the ES version on android
  //Remove boost stuff and no to scripting language->pure C++?
  Weight::Application* app=Weight::create_application();

  weight_engine_pointer->app->onAppCmd=app->handle_android_cmd;
  weight_engine_pointer->app->onInputEvent=app->event_system->handle_android_input;

  app->run(weight_engine_pointer);
  delete app;
}

#elif defined(WEIGHT_IOS)

#endif

#endif
