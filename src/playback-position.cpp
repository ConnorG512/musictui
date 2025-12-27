#include "playback-position.hpp"

auto PlaybackPosition::setPosition(const ma_uint64 pos) noexcept -> void 
{
  pcm_position_ = pos;
}

auto PlaybackPosition::getPosition() const noexcept -> const ma_uint64& 
{
  return pcm_position_;
}
