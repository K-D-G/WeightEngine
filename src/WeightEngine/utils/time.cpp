#include <WeightEngine/utils/time.h>

using namespace WeightEngine;

Time* Time::instance=0;

Time* Time::get(){
  if(instance==0){
    instance=new Time();
  }
  return instance;
}

#if defined(WEIGHT_DESKTOP)
Time::Time(){
  time_elapsed=0;
  last_frame_time=time_elapsed;
  time_step=0;
  glfwSetTime(0);
}

void Time::update(){
  time_elapsed=(float)glfwGetTime(); //Believed glfw returns in seconds
  time_step=time_elapsed-last_frame_time;
  last_frame_time=time_elapsed;
}
#elif defined(WEIGHT_ANDROID)
//Help from: https://stackoverflow.com/questions/3832097/how-to-get-the-current-time-in-native-android-code/3842017#3842017
Time::Time(){
  time_elapsed=0;
  last_frame_time=time_elapsed;
  time_step=0;
}

void Time::update(){
  timespec res;
  clock_gettime(CLOCK_REALTIME, &res);
  time_elapsed=(float)((1000.0*res.tv_spec+(double)res.tv_nsec/1e6)*0.001);
  time_step=time_elapsed-last_frame_time;
  last_frame_time=time_elapsed;
}
#endif
float Time::get_time_step(){
  return time_step;
}
float Time::get_time_elapsed(){
  return time_elapsed;
}
