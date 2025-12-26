#include "audio/volume.hpp"

Audio::Volume::Volume(const ma_sound &sound)
  : sound_instance_{sound}
  , current_volume_{ma_sound_get_volume(&sound_instance_)} 
{
  ma_sound_set_volume(&sound_instance_, current_volume_);
}

auto Audio::Volume::increaseVolume() noexcept -> void
{
  current_volume_ += volume_increment_;
  ma_sound_set_volume(&sound_instance_, current_volume_);
}

auto Audio::Volume::decreaseVolume() noexcept -> void
{
  current_volume_ -= volume_increment_;
  ma_sound_set_volume(&sound_instance_, current_volume_);
}
