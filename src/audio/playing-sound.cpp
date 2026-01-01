#include "audio/playing-sound.hpp"

#include <miniaudio/miniaudio.h>
#include <cassert>

auto Audio::playSound(ma_engine& engine, const char* sound_path) noexcept -> void
{
  assert(sound_path != nullptr);
  ma_engine_play_sound(&engine, sound_path, nullptr);
}

auto Audio::stopSound(ma_engine& engine, const char* sound_path) noexcept -> void
{
  assert(sound_path != nullptr);
  ma_engine_stop(&engine);
}

