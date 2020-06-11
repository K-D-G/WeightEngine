#ifndef WEIGHT_ENGINE__UTILS__TIME_H
#define WEIGHT_ENGINE__UTILS__TIME_H
#include <WeightEngine/core.h>
#include <WeightEngine/utils/log.h>

#if defined(WEIGHT_DESKTOP)
#include <GLFW/glfw3.h>
#elif defined(WEIGHT_ANDROID)
#include <time.h>
#endif

namespace Weight{
  class WEIGHT_API Time{
  private:
    static Time* instance;
    Time();
    Time(const Time&)=delete;
    Time& operator=(const Time&)=delete;

    float time_step;
    float time_elapsed;
    float last_frame_time;
  public:
    static Time* get();

    void update();
    float get_time_step();
    float get_time_elapsed();
  };
}

#endif
