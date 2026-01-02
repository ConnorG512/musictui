#pragma once 

#include <miniaudio/miniaudio.h>
#include <cstdint>

namespace Audio
{
  class VolumeHandler 
  {
    private:
      ma_sound& sound_instance_;
      float current_volume_{0.3};

    public:
      VolumeHandler(ma_sound& sound_instance, float volume);

      enum class Direction : std::uint8_t
      {
        increase, 
        decrease,
      };
      auto increaseVolume(float change_amount) noexcept -> float;
      auto decreaseVolume(float change_amount) noexcept -> float;
      auto setVolume(float change_amount) noexcept -> float;
  };
}
