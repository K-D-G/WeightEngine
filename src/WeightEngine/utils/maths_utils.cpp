#include <WeightEngine/utils/maths_utils.h>

using namespace WeightEngine;

float Maths::map(float n, float start, float stop, float start2, float stop2, bool constrain){
  float result=(n-start)/(stop-start)*(stop2-start2)+start2;
  if(constrain){
    if(start2<stop2){
      return Maths::constrain(result, start2, stop2);
    }else{
      return Maths::constrain(result, stop2, start2);
    }
  }
  return result;
}

float Maths::constrain(float n, float low, float high){
  return Maths::max(Maths::min(n, high), low);
}

float Maths::max(float a, float b){
  if(a>b){
    return a;
  }
  return b;
}

float Maths::min(float a, float b){
  if(a>b){
    return b;
  }
  return a;
}
