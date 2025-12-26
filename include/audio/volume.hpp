#pragma once

#include <miniaudio/miniaudio.h>

namespace Audio
{
class Volume
{
  public: 
    Volume(const ma_sound& sound);

  private:
    float current_volume_{0.0f};
    float volume_increment_{0.1f};
};
}
