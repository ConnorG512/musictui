#include "playback-position.hpp"
#include "track/track_instance.hpp"

PlaybackPosition::PlaybackPosition(ma_sound &track) : current_track_instance_{track} {}

auto PlaybackPosition::storeCurrentPCMPos() noexcept -> void
{
  ma_sound_get_cursor_in_pcm_frames(&current_track_instance_, &pcm_position_);
}

auto PlaybackPosition::getPosition() const noexcept -> const ma_uint64 & { return pcm_position_; }

auto PlaybackPosition::adjustCursorPos(const PositionDirection seek_type, const std::int32_t seconds) noexcept -> void
{
  storeCurrentPCMPos();

  ma_uint32 track_sample_rate{};
  ma_sound_get_data_format(&current_track_instance_, nullptr, nullptr, &track_sample_rate, nullptr, 0);

  ma_uint64 total_track_len{};
  ma_sound_get_length_in_pcm_frames(&current_track_instance_, &total_track_len);

  const ma_uint64 seek_offset{static_cast<ma_uint64>(track_sample_rate) * static_cast<ma_uint64>(seconds)};

  if (seek_type == PositionDirection::forward)
  {
    if (pcm_position_ + seek_offset >= total_track_len)
    {
      pcm_position_ = total_track_len - 1;
    }

    pcm_position_ += seek_offset;
  }
  else if (seek_type == PositionDirection::backward)
  {
    if (pcm_position_ - seek_offset < 0)
    {
      pcm_position_ = 0;
    }
    pcm_position_ -= seek_offset;
  }
}

auto PlaybackPosition::setPosition(ma_uint64 position) noexcept -> void
{
  ma_sound_seek_to_pcm_frame(&current_track_instance_, position);
}
