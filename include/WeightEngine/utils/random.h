#ifndef WEIGHT_ENGINE__UTILS__RANDOM_H
#define WEIGHT_ENGINE__UTILS__RANDOM_H
#include <random>

//Based of cherno's design
namespace Weight{
  class WEIGHT_API Random{
  private:
    static std::mt19937 random_engine;
    static std::uniform_int_distribution<std::mt19937::result_type> distribution;
  public:
    static void init();
    static float get_float();
  };
}

#endif
