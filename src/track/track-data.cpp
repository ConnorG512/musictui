#include "track/track-data.hpp"
#include "audio/engine.hpp"

#include <cassert>

Track::Data::Data(const char* file_path, Audio::Engine &engine)
  : data_instance_{CreateData(file_path, engine)} {}

Track::Data::~Data()
{
  destroyData();
}

auto Track::Data::CreateData(const char* file_path, Audio::Engine &engine) -> ma_sound 
{
  assert(file_path != nullptr);

  ma_sound track{};

  const auto result{ma_sound_init_from_file(engine.ptr(), file_path, 0, nullptr, nullptr, &track)};

  if (result != MA_SUCCESS)
    throw std::runtime_error("Failed to create sound!");

  return track;
}

auto Track::Data::destroyData() -> void 
{
  ma_sound_uninit(&data_instance_);
}

auto Track::Data::ref() noexcept -> ma_sound&
{
  return data_instance_;
}

auto Track::Data::cref() const noexcept -> const ma_sound& 
{
  return data_instance_;
}
