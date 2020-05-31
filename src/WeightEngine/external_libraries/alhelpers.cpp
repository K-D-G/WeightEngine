#include <ALLibraries/alhelpers.h>

bool OpenALHelpers::inited=false;

int OpenALHelpers::InitAL(std::string device_name){
  if(OpenALHelpers::inited){
    return 0;
  }
  ALCdevice* device=alcOpenDevice(device_name.c_str());
  if(!device){
    device=alcOpenDevice(NULL);
  }

  ALCcontext* ctx=alcCreateContext(device, NULL);
  if(ctx==NULL||alcMakeContextCurrent(ctx)==ALC_FALSE){
    if(ctx==NULL){
      alcDestroyContext(ctx);
    }
    alcCloseDevice(device);
    return -1;
  }
  OpenALHelpers::inited=true;
  return 0;
}
void OpenALHelpers::CloseAL(){
  ALCcontext* ctx=alcGetCurrentContext();
  if(ctx==NULL){
    return;
  }
  alcMakeContextCurrent(NULL);
  alcDestroyContext(ctx);
  alcCloseDevice(alcGetContextsDevice(ctx));
}
std::string OpenALHelpers::FormatName(ALenum format){
  switch(format){
    case AL_FORMAT_MONO8:return "Mono, U8";
    case AL_FORMAT_MONO16:return "Mono, S16";
    case AL_FORMAT_STEREO8:return "Stereo, U8";
    case AL_FORMAT_STEREO16:return "Stereo, S16";
    default:return "Unknown Format";
  }
}

std::vector<std::string> OpenALHelpers::GetAudioDevices(){
  if(alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT")==AL_FALSE){
    std::vector<std::string> result;
    result.push_back(NULL);
    return result;
  }
  const ALCchar* devices=alcGetString(NULL, ALC_DEVICE_SPECIFIER);

  std::vector<std::string> result;
  std::string temp;
  int len=0;
  while(true){
    if(devices[len]=='\0'&&devices[len+1]=='\0'){
      len+=2;
      break;
    }else{
      len+=1;
    }
  }

  for(int i=0; i<len; i++){
    if(devices[i]=='\0'){
      temp.clear();
    }else{
      temp+=devices[i];
    }
  }
  return result;
}
