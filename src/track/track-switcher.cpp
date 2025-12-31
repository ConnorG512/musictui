#include "track/track-switcher.hpp"

Track::Switcher::Switcher(int total_tracks, int current_track)
  : total_tracks_{total_tracks}
  , current_track_index_{current_track} {}

auto Track::Switcher::decreaseIndex() -> int 
{
  current_track_index_ += 1;
  if(current_track_index_ > total_tracks_)
    current_track_index_ = total_tracks_;
  return current_track_index_;
}

auto Track::Switcher::increaseIndex() -> int 
{
  current_track_index_ -= 1;
  if(current_track_index_ < 0)
    current_track_index_ = 0;
  return current_track_index_;
}
