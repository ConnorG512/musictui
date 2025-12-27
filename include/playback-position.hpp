#pragma once

#include <miniaudio/miniaudio.h>
#include <cstdint>

class TrackInstance;

class PlaybackPosition 
{
  public: 
    PlaybackPosition(ma_sound &track);
    auto storeCurrentPCMPos() noexcept -> void; 
    auto getPosition() const noexcept -> const ma_uint64&;
    auto setPosition(ma_uint64 position) noexcept -> void;

    enum class PositionDirection 
    {
      forward, 
      backward,
    };
    auto adjustCursorPos(const PositionDirection seek_type, const std::int32_t seconds = 3) noexcept -> void;

  private:
    ma_sound& current_track_instance_;
    ma_uint64 pcm_position_{0};
};
