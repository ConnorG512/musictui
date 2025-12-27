#include "track_instance.hpp"

#include <cassert>

TrackInstance::TrackInstance(const char* track_path, Audio::Engine& engine)
  : current_track_{createTrack(track_path, engine)}
  , track_volume{current_track_}
  , track_position(current_track_)
{
}

TrackInstance::~TrackInstance()
{
  ma_sound_uninit(&current_track_);
}

auto TrackInstance::createTrack(const char* track_path, Audio::Engine& engine) const -> ma_sound
{
  ma_sound track{};

  const auto result {ma_sound_init_from_file(
      engine.ptr(), 
      track_path, 
      0, 
      nullptr, 
      nullptr, 
      &track
  )};
  
  if (result != MA_SUCCESS)
    throw std::runtime_error("Failed to create sound!");

  return track;
}

auto TrackInstance::ref() noexcept -> ma_sound& 
{
  return current_track_;
}

auto TrackInstance::playTrack() noexcept -> void 
{
  ma_sound_start(&current_track_);
}

auto TrackInstance::pauseTrack() noexcept -> void 
{
  ma_sound_stop(&current_track_);
}

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
