#include "ui/window.hpp"

#include <cassert>

UI::Window::Window(const std::optional<std::pair<int, int>> dimensions_xy, std::pair<int, int> position_xy)
    : window_instance_{createBoxedWindow(dimensions_xy, position_xy)}
{
  refreshWindow();
}

auto UI::Window::refreshWindow() const noexcept -> void { wrefresh(window_instance_.get()); }

auto UI::Window::drawTextToWindow(const char *message, int x, int y) const noexcept -> void
{
  mvprintw(y, x, "%s", message);
}

auto UI::Window::createBoxedWindow(const std::optional<std::pair<int, int>> dimensions_xy,
                                   const std::pair<int, int> position_xy
    ) noexcept
    -> std::unique_ptr<WINDOW, decltype(&delwin)>
{
  WINDOW *created_window{nullptr};
  
  const auto& [pos_x, pos_y] = position_xy;
  if (dimensions_xy.has_value())
  {
    const auto &[size_x, size_y] = dimensions_xy.value();
    created_window = newwin(size_y, size_x, pos_y, pos_x);
    box(created_window, 0, 0);
  }
  else
  {
    created_window = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
    box(created_window, pos_y, pos_x);
  }
  assert(created_window != nullptr);

  wrefresh(created_window);

  return std::unique_ptr<WINDOW, decltype(&delwin)>{created_window, &delwin};
}
