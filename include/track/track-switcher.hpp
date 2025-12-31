#pragma once 

namespace Track 
{
  class Switcher
  {
    private:
      int total_tracks_ {0};
      int current_track_index_ {0};

    public:
      Switcher(int total_tracks, int current_track);
      auto increaseIndex() -> int;
      auto decreaseIndex() -> int;
  };
}
