#pragma once 

#include "audio/volume.hpp"

#include <miniaudio/miniaudio.h>

class TrackInstance 
{
  public: 
    TrackInstance(const char* track_path);
    ~TrackInstance();
  
  private:
    ma_sound current_track_; 
    Audio::Volume track_volume_;
};
