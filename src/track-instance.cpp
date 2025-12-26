#include "track_instance.hpp"

#include <cassert>

TrackInstance::TrackInstance(const char* track_path, Audio::Engine& engine)
  : current_track_{createTrack(track_path, engine)}
  , track_volume{current_track_}
{
}

TrackInstance::~TrackInstance()
{
  ma_sound_uninit(&current_track_);
}

auto TrackInstance::createTrack(const char* track_path, Audio::Engine& engine) const -> ma_sound
{
  ma_sound track{};

  const auto result {ma_sound_init_from_file(
      engine.ptr(), 
      track_path, 
      0, 
      nullptr, 
      nullptr, 
      &track
  )};
  
  if (result != MA_SUCCESS)
    throw std::runtime_error("Failed to create sound!");

  return track;
}
