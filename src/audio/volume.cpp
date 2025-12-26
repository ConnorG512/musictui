#include "audio/volume.hpp"

Audio::Volume::Volume(const ma_sound& sound)
  : current_volume_{ma_sound_get_volume(sound)} {}
