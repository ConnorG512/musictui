#pragma once

#include <miniaudio/miniaudio.h>

namespace Audio 
{
  [[maybe_unused]] auto setVolume(ma_sound& sound, float volume = 0.3) -> float;
}
