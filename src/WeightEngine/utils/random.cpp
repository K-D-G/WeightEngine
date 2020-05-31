#include <WeightEngine/utils/random.h>

using namespace Weight;

std::mt19937 Random::random_engine;
std::uniform_int_distribution<std::mt19937::result_type> Random::distribution;

void Random::init(){
  random_engine.seed();
}

float Random::get_float(){
  return (float)distribution(random_engine)/(float)std::numeric_limits<uint32_t>::max();
}
