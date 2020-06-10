#include <WeightEngine/android_wrappers/android_util_functions.h>
#if defined(WEIGHT_ANDROID)

ASensorManager* AcquireASensorManagerInstance(android_app* app){
  if(!app){
    return nullptr;
  }
  typedef ASensorManager *(*PF_GETINSTANCEFORPACKAGE)(const char* name);
  void* androidHandle=dlopen("libandroid.so", RTLD_NOW);
  auto getInstanceForPackageFunc=(PF_GETINSTANCEFORPACKAGE)dlsym(androidHandle, "ASensorManager_getInstanceForPackage");
  if(getInstanceForPackageFunc){
    JNIEnv* env=nullptr;
    app->activity->vm->AttachCurrentThread(&env, nullptr);

    jclass android_content_Context=env->GetObjectClass(app->activity->clazz);
    jmethodID midGetPackageName=env->GetMethodID(android_content_Context, "getPackageName", "()Ljava/lang/String;");
    auto packageName=(jstring)env->CallObjectMethod(app->activity->clazz, midGetPackageName);

    const char* nativePackageName=env->GetStringUTFChars(packageName, nullptr);
    ASensorManager* mgr=getInstanceForPackageFunc(nativePackageName);
    env->ReleaseStringUTFChars(packageName, nativePackageName);
    app->activity->vm->DetachCurrentThread();
    if(mgr){
      dlclose(androidHandle);
      return mgr;
    }
  }

  typedef ASensorManager *(PF_GETINSTANCE)();
  auto getInstanceFunc=(PF_GETINSTANCE)dlsym(androidHandle, "ASensorManager_getInstance");
  assert(getInstanceFunc);
  dlclose(androidHandle);
  return getInstanceFunc();
}

#endif
