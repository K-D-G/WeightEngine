#ifndef AL_HELPERS_H
#define AL_HELPERS_H
#include <ALLibraries/alut.h>

#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>

class OpenALHelpers{
public:
  static bool inited;
  static int InitAL(std::string device_name);
  static void CloseAL();
  static std::string FormatName(ALenum format);
  static std::vector<std::string> GetAudioDevices();
};

#endif
