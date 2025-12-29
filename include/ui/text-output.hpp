#pragma once

#include <ncurses.h>

#include <utility>
#include <span>
#include <optional>

namespace UI 
{
  class Window;

  namespace Text
  {
    auto drawStringsToScreen(
        WINDOW& window_instance, std::span<const char*> messages, 
        const std::pair<int, int> xy, std::optional<int> color = std::nullopt) noexcept -> void;
  }
}
