#pragma once

#include "audio/engine.hpp"
#include "audio/volume.hpp"
#include "playback-position.hpp"
#include "track/track-switcher.hpp"
#include "track/track-data.hpp"

#include <miniaudio/miniaudio.h>

class TrackInstance
{
public:
  TrackInstance(
      const char *track_path, Audio::Engine &engine, int total_tracks, int current_track);

private:
  Track::Data data_instance_;
  int current_track {};

public:
  Audio::Volume track_volume{current_track_};
  PlaybackPosition track_position;
  Track::Switcher Switcher{0,0};

  auto ref() noexcept -> ma_sound &;
  auto playTrack() noexcept -> void;
  auto pauseTrack() noexcept -> void;
  auto stopTrack() noexcept -> void;
  auto seekForward() noexcept -> void;
  auto seekBackward() noexcept -> void;
  auto swapTrack() noexcept -> void;
};
