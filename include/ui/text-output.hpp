#pragma once

#include <ncurses.h>

#include <utility>
#include <span>
#include <optional>
#include <cstddef>
#include <ranges>

namespace UI 
{
  class Window;
  
  namespace Text
  {
    template <std::size_t num_strings>
    struct Properties 
    {
      std::array<const char*, num_strings> messages {};
      std::array<std::pair<int, int>, num_strings> xy_positions {};
      std::optional<int> color {std::nullopt};
    };

    template <std::size_t num_strings>
    auto drawStringsToScreen(
        WINDOW* window_instance, const Properties<num_strings>& text_properties) noexcept -> void
    {
      if(text_properties.color.has_value())
        wattron(window_instance, text_properties.color.value());
      
      const auto& titles = std::views::zip(text_properties.messages, text_properties.xy_positions);
      for(const auto& [string, pos] : titles)
      {
        const auto& [x_pos, y_pos] = pos;

        mvprintw(y_pos, x_pos, "%s", string);
      }

      if(text_properties.color.has_value())
        wattroff(window_instance, text_properties.color.value());

    };
  }
}
