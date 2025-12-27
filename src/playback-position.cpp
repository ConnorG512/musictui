#include "playback-position.hpp"
#include "track_instance.hpp"

PlaybackPosition::PlaybackPosition(ma_sound &track)
  : current_track_instance_{track} {}

auto PlaybackPosition::storeCurrentPCMPos() noexcept -> void 
{
  ma_sound_get_cursor_in_pcm_frames(&current_track_instance_, &pcm_position_);
}

auto PlaybackPosition::getPosition() const noexcept -> const ma_uint64& 
{
  return pcm_position_;
}

auto PlaybackPosition::adjustCursorPos(const PositionDirection seek_type, const std::int32_t offset) noexcept -> void 
{
  pcm_position_ = getPosition();
  
  if(seek_type == PositionDirection::forward)
    pcm_position_ += offset;
  else if(seek_type == PositionDirection::backward)
  {
    if(pcm_position_ -= offset < 0)
      pcm_position_ = 0;

    pcm_position_ -= offset;
  }
}
