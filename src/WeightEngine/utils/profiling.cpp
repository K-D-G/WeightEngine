#include <WeightEngine/utils/profiling.h>
#ifdef WEIGHT_DEBUG

using namespace Weight;

ProfileAggregator* ProfileAggregator::instance=0;
ProfileAggregator* ProfileAggregator::get(){
  if(instance==0){
    instance=new ProfileAggregator();
  }
  return instance;
}

void ProfileAggregator::aggregate(std::string file_path){
  std::map<char*, ProfileJSONData> data;

  ProfileJSONData temp;
  for(int i=0; i<profiles.size(); i++){
    if(data.find(profiles[i].name)==data.end()){
      temp.number_runs=1;
      temp.min=profiles[i].time;
      temp.mean=profiles[i].time;
      temp.max=profiles[i].time;
      data[profiles[i].name]=temp;
    }else{
      data[profiles[i].name].number_runs++;
      data[profiles[i].name].min=std::min(data[profiles[i].name].min, profiles[i].time);
      data[profiles[i].name].max=std::max(data[profiles[i].name].max, profiles[i].time);
      data[profiles[i].name].mean=(data[profiles[i].name].mean*(data[profiles[i].name].number_runs-1)+profiles[i].time)/data[profiles[i].name].number_runs;
    }
  }

  json data_write;
  std::map<char*, ProfileJSONData>::iterator it;
  for(it=data.begin(); it!=data.end(); it++){
    data_write[it->first]={it->second.number_runs, it->second.min, it->second.mean, it->second.max};
  }

  Utils::write_file(file_path, data_write.dump());
}

ProfileAggregator::ProfileAggregator(){

}
ProfileAggregator::~ProfileAggregator(){

}

Profiler::Profiler(char* _name):name(_name), stopped(false){
  start_timepoint=std::chrono::high_resolution_clock::now();
}

Profiler::~Profiler(){
  if(!stopped){
    stop();
  }
}

void Profiler::stop(){
  std::chrono::time_point<std::chrono::steady_clock> end_timepoint=std::chrono::high_resolution_clock::now();

  long long start=std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint).time_since_epoch().count();
  long long end=std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();
  stopped=true;

  float duration=(end-start)*0.001f;
  Profile profile={name, duration};
  ProfileAggregator::get()->profiles.push_back(profile);
}
#endif
