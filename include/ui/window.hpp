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
  Window(const std::optional<std::pair<int, int>> dimensions_xy = std::nullopt,
         const std::pair<int, int> position_xy = {0,0});

  auto refreshWindow() const noexcept -> void;
  auto drawTextToWindow(const char *message, int x = 0, int y = 0) const noexcept -> void;
  
  auto ptr() const noexcept -> WINDOW*;
  auto cptr() const noexcept -> const WINDOW*;

private:
  auto createBoxedWindow(const std::optional<std::pair<int, int>> dimensions_xy,
                         const std::pair<int, int> position_xy
      ) noexcept
      -> std::unique_ptr<WINDOW, decltype(&delwin)>;

  std::unique_ptr<WINDOW, decltype(&delwin)> window_instance_{createBoxedWindow(std::nullopt, {0,0})};
};
} // namespace UI
