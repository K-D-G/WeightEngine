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

#elif defined(WEIGHT_IOS)

#endif

#endif
