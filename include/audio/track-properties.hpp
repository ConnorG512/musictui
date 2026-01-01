#pragma once 

#include <miniaudio/miniaudio.h>

namespace Audio
{
  class Properties
  {
    private:
      ma_sound& sound_;
      
      auto CreateProperties() -> void;

    public:
      ma_uint32 sample_rate{0};
      ma_uint32 channels{0};

      Properties(ma_sound& sound);
  };
}
