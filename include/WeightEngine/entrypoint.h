#ifndef WEIGHT_ENGINE__ENTRYPOINT_H
#define WEIGHT_ENGINE__ENTRYPOINT_H
#include <WeightEngine/core.h>
#include <WeightEngine/Application.h>

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

  if(weight_engine_pointer->app->savedState!=nullptr){
    weight_engine_pointer->state=*(Weight::Android::SavedState*)weight_engine_pointer->app->savedState;
  }

  Weight::Application* app=Weight::create_application();

  weight_engine_pointer->app->onAppCmd=app->_handle_android_cmd;
  weight_engine_pointer->app->onInputEvent=app->event_system->_handle_android_input;

  app->run(weight_engine_pointer);
  delete app;
}
#elif defined(WEIGHT_IOS)
#import <UIKit/UIKit.h>
#import <WeightEngine/ios_wrappers/AppDelegate.h>

int main(int argc, char* argv[]){
  NSString* app_delegate_class_name;
  @autoreleasepool{
    app_delegate_class_name=NSStringFromClass([AppDelegate class]);
  }
  return UIApplicationMain(argc, argv, nil, app_delegate_class_name);
}

#endif

#endif
