#ifndef WEIGHT_ENGINE__UTILS__MATHS_UTILS_H
#define WEIGHT_ENGINE__UTILS__MATHS_UTILS_H
#include <WeightEngine/core.h>

namespace WeightEngine{
  class WEIGHT_API Maths{
  public:
    //Help from p5.js
    static float map(float n, float start, float stop, float start2, float stop2, bool constrain=true);
    static float constrain(float n, float low, float high);
    static float max(float a, float b);
    static float min(float a, float b);
  };
}

#endif
