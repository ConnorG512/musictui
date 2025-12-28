#include "ui/window.hpp"

UI::Window::Window(const int x, const int y)
  : window_instance_{createBoxedWindow(x, y)} {}

auto UI::Window::createBoxedWindow(const int x, const int y) noexcept -> std::unique_ptr<WINDOW, decltype(&delwin)> 
{
  WINDOW* created_window { newwin(y, x, 0, 0)};
  box(created_window, 0, 0);
  wrefresh(created_window);
  
  return std::unique_ptr<WINDOW, decltype(&delwin)> {created_window, &delwin};
}
