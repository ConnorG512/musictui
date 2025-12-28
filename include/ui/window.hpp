#pragma once 

#include <memory>
#include <ncurses.h>

namespace UI 
{
  class Window
  {
    public:
      Window(const int x, const int y);

      auto refreshWindow() const noexcept -> void;
      auto drawTextToWindow(const char * message, int x = 0, int y = 0) const noexcept -> void;

    private:
      auto createBoxedWindow(const int x = 10, const int y = 20) noexcept 
        -> std::unique_ptr<WINDOW, decltype(&delwin)>;
      
      std::unique_ptr<WINDOW, decltype(&delwin)> window_instance_ {createBoxedWindow()}; 
  };
}
