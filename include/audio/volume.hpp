#pragma once

#include <miniaudio/miniaudio.h>

namespace Audio
{
class Volume
{
  public: 
    Volume(const ma_sound &sound);
    auto increaseVolume() noexcept -> void;
    auto decreaseVolume() noexcept -> void;

  private:
    ma_sound sound_instance_{};
    float current_volume_{0.0f};
    float volume_increment_{0.1f};
};
}
