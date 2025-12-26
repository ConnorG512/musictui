#pragma once

#include <miniaudio/miniaudio.h>

namespace Audio
{
class Volume
{
  public: 
    Volume(ma_sound &sound);

    auto increaseVolume() noexcept -> float;
    auto decreaseVolume() noexcept -> float;

  private:
    ma_sound &sound_instance_;
    float current_volume_{0.5f};
    float volume_increment_{0.1f};
};
}
