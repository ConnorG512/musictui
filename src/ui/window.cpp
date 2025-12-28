#include "ui/window.hpp"

auto createBoxedWindow() noexcept -> std::unique_ptr<WINDOW, decltype(&delwin)> 
{
  WINDOW* created_window { newwin(20, 10, 0, 0)};
  box(created_window, 0, 0);
  wrefresh(created_window);
  
  return std::unique_ptr<WINDOW, decltype(&delwin)> {created_window, &delwin};
}
