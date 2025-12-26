#include "audio/volume.hpp"

Audio::Volume::Volume(const ma_sound &sound)
  : sound_instance_{sound}
  , current_volume_{ma_sound_get_volume(&sound_instance_)} {}

auto Audio::Volume::increaseVolume() noexcept -> void
{
  current_volume_ += volume_increment_;
}

auto Audio::Volume::decreaseVolume() noexcept -> void
{
  current_volume_ -= volume_increment_;
}
