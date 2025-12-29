#pragma once

#include "ncurses.h"

#include <utility>
#include <span>

namespace UI 
{
  class Window;

  namespace Text
  {
    auto drawStringToScreen(
        const UI::Window& window_instance, const char* message, const std::pair<int, int> xy) noexcept -> void;

    auto drawColouredString(const UI::Window& window_instance, std::span<const char>(message)) -> void;
  }
}
