#pragma once

#include <miniaudio/miniaudio.h>

namespace Audio 
{
  auto setVolume(ma_sound& sound, float volume = 0.3) -> void;
}
