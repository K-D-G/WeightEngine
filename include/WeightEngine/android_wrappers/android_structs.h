#ifndef WEIGHT_ENGINE__ANDROID_WRAPPERS__ANDROID_STRUCTS_H
#define WEIGHT_ENGINE__ANDROID_WRAPPERS__ANDROID_STRUCTS_H
#include <WeightEngine/core.h>
#if defined(WEIGHT_ANDROID)
#include <memory>
#include <jni.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <WeightEngine/android_wrappers/android_native_app_glue.h>

namespace Weight{
  namespace Android{
    struct SavedState{

    };

    struct WeightState{
      android_app* app;

      ASensorManager* sensor_manager;
      const ASensor* accelerometer;
      ASensorEventQueue* sensor_event_queue;

      EGLDisplay display;
      EGLSurface surface;
      EGLContext context;
      int width;
      int height;

      SavedState saved_state;
    };
  }
}

#endif
#endif
