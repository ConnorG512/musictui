#include "ui/text-output.hpp"
#include "ui/window.hpp"

#include <cassert>

auto UI::Text::drawStringsToScreen(
    WINDOW& window_instance, std::span<const char*> messages, 
    const std::pair<int, int> xy, std::optional<int> color) noexcept -> void
{
  assert(messages.data() != nullptr);
  
  if(color.has_value())
    wattron(&window_instance, color.value());

  const auto& [x, y] = xy;
  for(const auto& message : messages)
  {
    assert(message != nullptr);
    mvprintw(y, x, "%s", message);
  }
  
  if(color.has_value())
    wattroff(&window_instance, color.value());
}
