#include "audio/volume.hpp"

auto Audio::setVolume(ma_sound& sound, float volume) -> void
{
  if (volume > 1.0)
    ma_sound_set_volume(&sound, 1.0);
  else if (volume < 0.0)
    ma_sound_set_volume(&sound, 0.0);
  else 
    ma_sound_set_volume(&sound, volume);

}
