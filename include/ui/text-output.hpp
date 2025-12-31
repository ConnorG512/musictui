#pragma once

#include <ncurses.h>

#include <utility>
#include <span>
#include <optional>
#include <cstddef>
#include <ranges>
#include <print>

namespace UI 
{
  class Window;
  
  namespace Text
  {
    struct Properties 
    {
      std::span<std::string> strings{};
      std::span<std::pair<int, int>> xy_positions {};
      std::optional<int> color {std::nullopt};
    };

    auto drawVerticalStringList(
        WINDOW* window_instance, std::span<const std::string> string_list, std::pair<int,int> xy) noexcept -> void
    {
      const auto& [x_pos, y_pos] = xy;
      auto vertical_pos {y_pos};

      for(const auto& string : string_list)
      {
        mvprintw(vertical_pos, x_pos, "%s", string.c_str());
        vertical_pos += 1;
      }

      wrefresh(window_instance);
    };
  }
}
