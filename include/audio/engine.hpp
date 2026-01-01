#pragma once

#include <memory>
#include <miniaudio/miniaudio.h>

namespace Audio
{
class Engine
{
public:
  Engine();
  ~Engine();

  Engine(const Engine &other) = delete;
  Engine &operator=(const Engine &other) = delete;
  Engine(Engine &&other) noexcept = delete;
  Engine &operator=(Engine &&other) noexcept = delete;

  auto ref() noexcept -> ma_engine&;
  auto cref() const noexcept -> const ma_engine&;

private:
  ma_engine engine_{};
};
} // namespace Audio
