#include "track/track_instance.hpp"

#include <cassert>

TrackInstance::TrackInstance(const char *track_path, Audio::Engine &engine, int total_tracks, int current_track)
    : current_track_{createTrack(track_path, engine)}, track_volume{current_track_}, track_position(current_track_)
    , Switcher{total_tracks, current_track}
{
}

auto TrackInstance::ref() noexcept -> ma_sound & { return current_track_; }

auto TrackInstance::playTrack() noexcept -> void { ma_sound_start(&current_track_); }

auto TrackInstance::pauseTrack() noexcept -> void { ma_sound_stop(&current_track_); }

auto TrackInstance::stopTrack() noexcept -> void
{
  ma_sound_stop(&current_track_);
  track_position.setPosition(0);
}

auto TrackInstance::seekForward() noexcept -> void
{
  track_position.adjustCursorPos(PlaybackPosition::PositionDirection::forward, 3);
  ma_sound_seek_to_pcm_frame(&current_track_, track_position.getPosition());
  ma_sound_start(&current_track_);
}

auto TrackInstance::seekBackward() noexcept -> void
{
  track_position.adjustCursorPos(PlaybackPosition::PositionDirection::backward, 3);
  ma_sound_seek_to_pcm_frame(&current_track_, track_position.getPosition());
  ma_sound_start(&current_track_);
}

auto TrackInstance::swapTrack() noexcept -> void
{
  stopTrack();
  
}
