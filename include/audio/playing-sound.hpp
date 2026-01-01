#pragma once

#include "miniaudio/miniaudio.h"

namespace Audio 
{
  class PlayingSound 
  {
    private: 
      PlayingSound(ma_engine& engine, const char* file_path);
      ~PlayingSound();

      ma_engine& engine_;
      ma_sound sound_instance_{};

      auto CreateSound(ma_engine& engine, const char* file_path) const -> ma_sound;

    public:
      auto clearSound() noexcept -> void;
      auto resetSound(const char* file_path);
  };
}
