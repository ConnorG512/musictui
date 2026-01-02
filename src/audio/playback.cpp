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

auto Audio::Playback::seekForward(ma_sound& sound, ma_uint32 sample_rate) noexcept -> void
{
  ma_uint64 track_cursor{};
  ma_sound_get_cursor_in_pcm_frames(&sound, &track_cursor);
}

auto Audio::Playback::seekBackward(ma_sound& sound, ma_uint32 sample_rate) noexcept -> void 
{

}
