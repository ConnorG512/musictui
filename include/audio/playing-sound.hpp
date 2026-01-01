#pragma once

#include "miniaudio/miniaudio.h"

namespace Audio 
{
  class PlayingSound 
  {
    private: 
      ma_engine& engine_;
      ma_sound sound_instance_{};

      auto CreateSound(ma_engine& engine, const char* file_path) const -> ma_sound;

    public:
      PlayingSound(ma_engine& engine, const char* file_path);
      ~PlayingSound();
      
      auto clearSound() noexcept -> void;
      auto resetSound(const char* file_path);
  };
}
