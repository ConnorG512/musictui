#include "ui/text-output.hpp"
#include "ui/window.hpp"

#include <cassert>

auto UI::Text::drawStringToScreen(
    const UI::Window& window_instance, const char* message, const std::pair<int, int> xy) noexcept -> void
{
  assert(message != nullptr);

  const auto& [x, y] = xy;
  mvprintw(y, x, "%s", message);
}

auto UI::Text::drawColouredString(const UI::Window& window_instance, std::span<const char>(message)) -> void
{
  assert(message.data() != nullptr);
}
