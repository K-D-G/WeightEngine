#include <WeightEngine/utils/time.h>

using namespace Weight;

Time* Time::instance=0;

Time* Time::get(){
  if(instance==0){
    instance=new Time();
  }
  return instance;
}

#ifdef WEIGHT_USE_GLFW
Time::Time(){
  time_elapsed=(float)glfwGetTime();
  last_frame_time=time_elapsed;
  time_step=0;
}

void Time::update(){
  time_elapsed=(float)glfwGetTime();
  time_step=time_elapsed-last_frame_time;
  last_frame_time=time_elapsed;
}
#else
Time::Time(){

}

void Time::update(){
  
}
#endif
float Time::get_time_step(){
  return time_step;
}
float Time::get_time_elapsed(){
  return time_elapsed;
}
