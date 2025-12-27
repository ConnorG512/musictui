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
