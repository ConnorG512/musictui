#include "audio/volume.hpp"

Audio::Volume::Volume(ma_sound &sound)
  : sound_instance_{sound}
  , current_volume_{ma_sound_get_volume(&sound_instance_)} 
{
  ma_sound_set_volume(&sound_instance_, current_volume_);
}

auto Audio::Volume::increaseVolume() noexcept -> float
{
  current_volume_ += volume_increment_;
  if (current_volume_ > 1.0f)
    current_volume_ = 1.0f;

  ma_sound_set_volume(&sound_instance_, current_volume_);
  return current_volume_;
}

auto Audio::Volume::decreaseVolume() noexcept -> float
{
  current_volume_ -= volume_increment_;
  if (current_volume_ < 0.0f)
    current_volume_ = 0.0f;

  ma_sound_set_volume(&sound_instance_, current_volume_);
  return current_volume_;
}
