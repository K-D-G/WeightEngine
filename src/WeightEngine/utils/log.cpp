#include <WeightEngine/utils/log.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace WeightEngine;

std::shared_ptr<spdlog::logger> Log::engine_logger;
std::shared_ptr<spdlog::logger> Log::app_logger;

void Log::init(std::string name){
  spdlog::set_pattern("%^[%T] %n: %v%$");
  engine_logger=spdlog::stdout_color_mt("WEIGHT");
  engine_logger->set_level(spdlog::level::trace);

  app_logger=spdlog::stdout_color_mt(name);
  app_logger->set_level(spdlog::level::trace);
}
