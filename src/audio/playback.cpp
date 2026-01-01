#include "audio/playback.hpp"

#include <stdexcept>
#include <format>

auto Audio::Playback::startPlayback(ma_sound& sound) -> void 
{
  if(const auto result = ma_sound_start(&sound); result != MA_SUCCESS)
  {
    throw std::runtime_error(std::format("Failed to start sound! Error {}", static_cast<int>(result)));
  }
}

auto Audio::Playback::stopPlayback(ma_sound& sound) -> void 
{
  if(const auto result = ma_sound_stop(&sound); result != MA_SUCCESS)
  {
    throw std::runtime_error(std::format("Failed to stop sound! Error {}", static_cast<int>(result)));
  }
}
