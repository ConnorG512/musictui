#include "ui/text-output.hpp"
#include "ui/window.hpp"

#include <cassert>
#include <ranges>

auto UI::Text::drawStringsToScreen(
    WINDOW* window_instance, std::span<const char*> messages, 
    const std::span<std::pair<int, int>> xy, const std::optional<int> color) noexcept -> void
{
  assert(messages.data() != nullptr && xy.data() != nullptr);

  if(color.has_value())
    wattron(window_instance, color.value());
  
  const auto& titles = std::views::zip(messages, xy);
  for(const auto& [string, pos] : titles)
  {
    assert(string != nullptr);
    const auto& [x_pos, y_pos] = pos;

    mvprintw(y_pos, x_pos, "%s", string);
  }

  if(color.has_value())
    wattroff(window_instance, color.value());
}
  
