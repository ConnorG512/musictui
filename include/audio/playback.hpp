#pragma once

#include <miniaudio/miniaudio.h>

namespace Audio::Playback 
{
  auto startPlayback(ma_sound& sound) -> void;
  auto stopPlayback(ma_sound& sound) -> void;
  auto seekForward(ma_sound& sound, ma_uint32 sample_rate) noexcept -> void;
  auto seekBackward(ma_sound& sound, ma_uint32 sample_rate) noexcept -> void;
}
