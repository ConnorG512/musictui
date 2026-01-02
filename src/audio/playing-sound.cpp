#include "audio/playing-sound.hpp"

#include <miniaudio/miniaudio.h>
#include <cassert>
#include <stdexcept>

Audio::PlayingSound::PlayingSound(ma_engine& engine, const char* file_path)
  : engine_{engine}
{
  createSound(engine_, file_path);
}

Audio::PlayingSound::~PlayingSound()
{
  clearSound();
}

auto Audio::PlayingSound::createSound(ma_engine& engine, const char* file_path) -> void
{ 
  assert(file_path != nullptr);

  if(const auto result = ma_sound_init_from_file(&engine, file_path, 0, nullptr, nullptr, &sound_instance_);
      result != MA_SUCCESS)
  {
    throw std::runtime_error("Failed to create sound instance from file!");
  }
}

auto Audio::PlayingSound::clearSound() noexcept -> void
{
  ma_sound_uninit(&sound_instance_);
}

auto Audio::PlayingSound::resetSound(const char* file_path) -> void
{
  assert(file_path != nullptr);
  
  ma_sound_stop(&sound_instance_);
  clearSound();
  createSound(engine_, file_path);
}

auto Audio::PlayingSound::ref() noexcept -> ma_sound&
{
  return sound_instance_;
}

auto Audio::PlayingSound::cref() const noexcept -> const ma_sound&
{
  return sound_instance_;
}
