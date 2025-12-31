#pragma once 

#include <utility>

namespace Track 
{
  class Switcher
  {
    private:
      int total_tracks_ {0};
      int current_track_index_ {0};

    public:
      auto increaseIndex() -> int;
      auto decreaseIndex() -> int;
  };
}
