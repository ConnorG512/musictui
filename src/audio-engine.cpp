#include "audio-engine.hpp"

#include <stdexcept>
#include <print>

Audio::Engine::Engine()
{
  if(const auto result = ma_engine_init(nullptr, &engine_); result != MA_SUCCESS)
  {
    throw std::runtime_error(std::format(
          "Failed to create audio engine! Erorr {}", static_cast<int>(result)));
  }
}

auto Audio::Engine::ptr() const noexcept -> const ma_engine* 
{
  return &engine_;
}
