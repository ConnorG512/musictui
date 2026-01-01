#include "audio/playing-sound.hpp"

#include <miniaudio/miniaudio.h>
#include <cassert>
#include <stdexcept>

Audio::PlayingSound::PlayingSound(ma_engine& engine, const char* file_path)
  : engine_{engine}
  , sound_instance_{CreateSound(engine_, file_path)} {}

Audio::PlayingSound::~PlayingSound()
{
  clearSound();
}

auto Audio::PlayingSound::CreateSound(ma_engine& engine, const char* file_path) const -> ma_sound
{
  assert(file_path != nullptr);
  ma_sound sound {};

  if(const auto result = ma_sound_init_from_file(&engine, file_path, 0, nullptr, nullptr, &sound);
      result != MA_SUCCESS)
  {
    throw std::runtime_error("Failed to create sound instance from file!");
  }
  return sound;
}

auto Audio::PlayingSound::clearSound() noexcept -> void
{
  ma_sound_uninit(&sound_instance_);
}

auto Audio::PlayingSound::resetSound(const char* file_path)
{
  assert(file_path != nullptr);
  
  clearSound();
  sound_instance_ = CreateSound(engine_, file_path);
}

auto Audio::PlayingSound::ref() noexcept -> ma_sound&
{
  return sound_instance_;
}

auto Audio::PlayingSound::cref() const noexcept -> const ma_sound&
{
  return sound_instance_;
}
