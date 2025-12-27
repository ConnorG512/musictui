#pragma once

#include <miniaudio/miniaudio.h>

class TrackInstance;

class PlaybackPosition 
{
  public: 
    PlaybackPosition(ma_sound &track);
    auto storeCurrentPCMPos() noexcept -> void; 
    auto getPosition() const noexcept -> const ma_uint64&;

  private:
    ma_sound& current_track_instance_;
    ma_uint64 pcm_position_{0};
};
