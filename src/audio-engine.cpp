#include "audio-engine.hpp"

#include <stdexcept>

Audio::Engine::Engine()
{
  if(const auto result = ma_engine_init(nullptr, engine_.get()); result != MA_SUCCESS)
  {
    throw std::runtime_error("Failed to create miniaudio engine!");
  }
}

auto Audio::Engine::ptr() const noexcept -> ma_engine* 
{
  return engine_.get();
}
