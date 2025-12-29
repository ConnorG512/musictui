#pragma once

#include <memory>
#include <ncurses.h>
#include <optional>
#include <utility>

namespace UI
{
class Window
{
public:
  Window(const std::optional<std::pair<int, int>> dimensions_xy = std::nullopt);

  auto refreshWindow() const noexcept -> void;
  auto drawTextToWindow(const char *message, int x = 0, int y = 0) const noexcept -> void;

private:
  auto createBoxedWindow(const std::optional<std::pair<int, int>> dimensions_xy) noexcept
      -> std::unique_ptr<WINDOW, decltype(&delwin)>;

  std::unique_ptr<WINDOW, decltype(&delwin)> window_instance_{createBoxedWindow(std::nullopt)};
};
} // namespace UI
