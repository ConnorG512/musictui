#include "audio/engine.hpp"

#include <print>
#include <stdexcept>

Audio::Engine::Engine()
{
  if (const auto result = ma_engine_init(nullptr, &engine_); result != MA_SUCCESS)
  {
    throw std::runtime_error(std::format("Failed to create audio engine! Erorr {}", static_cast<int>(result)));
  }
}

Audio::Engine::~Engine() { ma_engine_uninit(&engine_); }

auto Audio::Engine::ref() noexcept -> ma_engine&
{
  return engine_;
}

auto Audio::Engine::cref() const noexcept -> const ma_engine&
{
  return engine_;
}
