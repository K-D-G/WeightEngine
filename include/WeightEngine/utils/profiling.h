#ifndef WEIGHT_ENGINE__UTILS__PROFILING_H
#define WEIGHT_ENGINE__UTILS__PROFILING_H
#include <WeightEngine/core.h>
#ifdef WEIGHT_DEBUG
#include <WeightEngine/utils/utils.h>

#include <json.h>

using json=nlohmann::json;

#include <chrono>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

//Help from the cherno
namespace WeightEngine{
  struct WEIGHT_API Profile{
    char* name;
    float time;
  };

  struct WEIGHT_API ProfileJSONData{
    int number_runs;
    float min, mean, max;
  };

  class WEIGHT_API ProfileAggregator{
  private:
    static ProfileAggregator* instance;
    ProfileAggregator();
    ~ProfileAggregator();
    ProfileAggregator(const ProfileAggregator&)=delete;
    ProfileAggregator& operator=(const ProfileAggregator&)=delete;
  public:
    std::vector<Profile> profiles;
    void aggregate(std::string file_path);

    static ProfileAggregator* get();
  };

  class Profiler{
  private:
    char* name;
    std::chrono::time_point<std::chrono::steady_clock> start_timepoint;
    bool stopped;
  public:
    Profiler(char* _name);
    ~Profiler();
    void stop();
  };
}

#define WEIGHT_PROFILE(name) WeightEngine::Profiler p(name)
#else
#define WEIGHT_PROFILE(name) //
#endif
#endif
