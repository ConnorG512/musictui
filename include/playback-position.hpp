#pragma once

#include <miniaudio/miniaudio.h>

class PlaybackPosition 
{
  public: 
    auto setPosition(const ma_uint64 pos) noexcept -> void;
    auto getPosition() const noexcept -> const ma_uint64&;

  private:
    ma_uint64 pcm_position{0};
};
