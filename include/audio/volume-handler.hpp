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
      VolumeHandler(ma_sound& sound_instance, float volume)
        : sound_instance_{sound_instance}, current_volume_{volume} {}

      enum class Direction : std::uint8_t
      {
        increase, 
        decrease,
      };
      auto increaseVolume(Direction direction, float change_amount) noexcept -> float;
      auto decreaseVolume(Direction direction, float change_amount) noexcept -> float;
      auto setVolume(float change_amount) noexcept -> float;
  };
}
