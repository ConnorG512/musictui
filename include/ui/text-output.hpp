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

    auto drawStringsToScreen(
        WINDOW* window_instance, std::span<const std::string> text_properties) noexcept -> void
    {
//      if(text_properties.color.has_value())
//        wattron(window_instance, text_properties.color.value());
//
//      const auto& titles = std::views::zip(text_properties, text_properties.xy_positions);
//      for(const auto& [string, pos] : titles)
//      {
//        const auto& [x_pos, y_pos] = pos;
//
//        mvprintw(y_pos, x_pos, "%s", string);
//      }
//
//      if(text_properties.color.has_value())
//        wattroff(window_instance, text_properties.color.value());
//      
//      wrefresh(window_instance);
    };
  }
}
