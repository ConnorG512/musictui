#include "audio/engine.hpp"
#include <stdexcept>

Audio::Engine::Engine()
  : engine_{CreateEngine()} {}

Audio::Engine::~Engine()
{
  ma_engine_uninit(&engine_);
}
auto Audio::Engine::CreateEngine() -> ma_engine 
{
  ma_engine engine {};

  const auto result {ma_engine_init(nullptr, &engine)};
  if (result != MA_SUCCESS)
  {
    throw std::runtime_error("Failed to create audio engine!");
  }

  return engine;
}

auto Audio::Engine::cref() const noexcept -> const ma_engine&
{
  return engine_;
}

auto Audio::Engine::ref() noexcept -> ma_engine& 
{
  return engine_;
}
