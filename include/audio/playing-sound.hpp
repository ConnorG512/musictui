#pragma once

#include "miniaudio/miniaudio.h"

namespace Audio 
{
  class PlayingSound 
  {
    private: 
      ma_engine& engine_;
      ma_sound sound_instance_{};

      auto createSound(ma_engine& engine, const char* file_path) -> void;
      auto clearSound() noexcept -> void;

    public:
      PlayingSound(ma_engine& engine, const char* file_path);
      ~PlayingSound();
      
      auto resetSound(const char* file_path) -> void;
      
      auto ref() noexcept -> ma_sound&;
      auto cref() const noexcept -> const ma_sound&;
  };
}
