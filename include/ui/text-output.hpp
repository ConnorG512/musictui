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
      
      wrefresh(window_instance);
    };
  }

  constexpr Text::Properties<7> user_controls 
  {
    .messages = {
      "Decrease Volume: F1",
      "Increase Volume: F2",
      "Pause: F3",
      "Play: F4",
      "Seek Backward: F5",
      "Seek Forward: F6",
      "Stop: F7",
    },
    .xy_positions = {{
      {1,10},
      {1,11},
      {1,12},
      {1,13},
      {1,14},
      {1,15},
      {1,16}
    }},
    .color = std::nullopt,
  };
}
