#pragma once

#include "miniaudio/miniaudio.h"

namespace Audio 
{
  auto playSound(ma_engine& engine, const char* sound_path) noexcept -> void;
  auto stopSound(ma_engine& engine, const char* sound_path) noexcept -> void;
}
