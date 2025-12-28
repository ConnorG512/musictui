#pragma once 

#include <memory>
#include <ncurses.h>

namespace UI 
{
  class Window
  {
    public:
      Window(const int x, const int y);

    private:
      auto createBoxedWindow(const int x = 10, const int y = 20) noexcept 
        -> std::unique_ptr<WINDOW, decltype(&delwin)>;
      
      std::unique_ptr<WINDOW, decltype(&delwin)> window_instance_ {createBoxedWindow()}; 
  };
}
