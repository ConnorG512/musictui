#pragma once

#include <miniaudio/miniaudio.h>

namespace Audio { class Engine; }

namespace Track 
{
  struct Data 
  {
    private:
      ma_sound data_instance_ {};

    public:
      Data(const char* file_path, Audio::Engine &engine);
      ~Data();
      
      auto CreateData(const char* file_path, Audio::Engine &engine) -> ma_sound;
      auto destroyData() -> void;
  };
}
