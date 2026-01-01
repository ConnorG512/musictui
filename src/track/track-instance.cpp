#include "track/track_instance.hpp"

#include <cassert>

TrackInstance::TrackInstance(const char *track_path, Audio::Engine &engine, int total_tracks, int current_track)
    : data_instance_{track_path, engine}
    , track_volume{data_instance_.ref()}
    , track_position(data_instance_.ref())
    , Switcher{total_tracks, current_track}
{
}

auto TrackInstance::ref() noexcept -> ma_sound & { return data_instance_.ref(); }

auto TrackInstance::playTrack() noexcept -> void { ma_sound_start(&data_instance_.ref()); }

auto TrackInstance::pauseTrack() noexcept -> void { ma_sound_stop(&data_instance_.ref()); }

auto TrackInstance::stopTrack() noexcept -> void
{
  ma_sound_stop(&data_instance_.ref());
  track_position.setPosition(0);
}

auto TrackInstance::seekForward() noexcept -> void
{
  track_position.adjustCursorPos(PlaybackPosition::PositionDirection::forward, 3);
  ma_sound_seek_to_pcm_frame(&data_instance_.ref(), track_position.getPosition());
  ma_sound_start(&data_instance_.ref());
}

auto TrackInstance::seekBackward() noexcept -> void
{
  track_position.adjustCursorPos(PlaybackPosition::PositionDirection::backward, 3);
  ma_sound_seek_to_pcm_frame(&data_instance_.ref(), track_position.getPosition());
  ma_sound_start(&data_instance_.ref());
}

auto TrackInstance::swapTrack() noexcept -> void
{
  stopTrack();
  
}
