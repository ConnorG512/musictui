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

  Engine(const Engine &other) = default;
  Engine &operator=(const Engine &other) = default;
  Engine(Engine &&other) noexcept = default;
  Engine &operator=(Engine &&other) noexcept = default;

  auto ref() noexcept -> ma_engine&;
  auto cref() const noexcept -> const ma_engine&;

private:
  ma_engine engine_{};
};
} // namespace Audio
