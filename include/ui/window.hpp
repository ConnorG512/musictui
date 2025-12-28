#pragma once 

#include <memory>
#include <ncurses.h>

namespace UI 
{
  class Window
  {
    public:
      Window() = default;
      ~Window();

    private:
      auto createBoxedWindow() noexcept -> std::unique_ptr<WINDOW, decltype(&delwin)>;
      
      std::unique_ptr<WINDOW, decltype(&delwin)> window_instance_ {createBoxedWindow()}; 
  };
}
