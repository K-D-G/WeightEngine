#ifndef WEIGHT_ENGINE__ANDROID_WRAPPERS__ANDROID_UTIL_FUNCTIONS_H
#define WEIGHT_ENGINE__ANDROID_WRAPPERS__ANDROID_UTIL_FUNCTIONS_H
#include <WeightEngine/core.h>
#if defined(WEIGHT_ANDROID)
#include <WeightEngine/android_wrappers/android_native_app_glue.h>
#include <android/sensor.h>
#include <jni.h>
#include <dlfcn.h>
#include <cassert>

//From NDK examples on Android github->Here because of a deprecation issue
ASensorManager* AcquireASensorManagerInstance(android_app* app);

#endif
#endif
