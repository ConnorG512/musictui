#include "ui/window.hpp"

UI::Window::Window(const std::optional<std::pair<int, int>> dimensions_xy)
  : window_instance_{createBoxedWindow(x, y)} 
{
  refreshWindow();
}

auto UI::Window::refreshWindow() const noexcept -> void 
{
  wrefresh(window_instance_.get());
}
auto UI::Window::drawTextToWindow(const char * message, int x, int y) const noexcept -> void 
{
  mvprintw(y, x, "%s", message);
}

auto UI::Window::createBoxedWindow(const std::optional<std::pair<int, int>> dimensions_xy) noexcept 
  -> std::unique_ptr<WINDOW, decltype(&delwin)> 
{
  WINDOW* created_window {newwin(y, x, 0, 0)};
  box(created_window, 0, 0);
  wrefresh(created_window);
  
  return std::unique_ptr<WINDOW, decltype(&delwin)> {created_window, &delwin};
}

