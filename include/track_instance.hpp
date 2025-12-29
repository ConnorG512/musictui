#pragma once

#include "audio/engine.hpp"
#include "audio/volume.hpp"
#include "playback-position.hpp"

#include <miniaudio/miniaudio.h>

class TrackInstance
{
public:
  TrackInstance(const char *track_path, Audio::Engine &engine);
  ~TrackInstance();

private:
  ma_sound current_track_{};

  auto createTrack(const char *track_path, Audio::Engine &engine) const -> ma_sound;

public:
  Audio::Volume track_volume{current_track_};
  PlaybackPosition track_position;

  auto ref() noexcept -> ma_sound &;
  auto playTrack() noexcept -> void;
  auto pauseTrack() noexcept -> void;
  auto stopTrack() noexcept -> void;
  auto seekForward() noexcept -> void;
  auto seekBackward() noexcept -> void;
};
