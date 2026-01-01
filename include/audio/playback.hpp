#pragma once

#include <miniaudio/miniaudio.h>

namespace Audio::Playback 
{
  auto startPlayback(ma_sound& sound) -> void;
  auto stopPlayback(ma_sound& sound) -> void;
}
