#pragma once 

#include <memory>
#include <optional>
#include <utility>
#include <ncurses.h>


namespace UI 
{
  class Window
  {
    public:
      Window(const std::optional<std::pair<int, int>> dimensions_xy);

      auto refreshWindow() const noexcept -> void;
      auto drawTextToWindow(const char * message, int x = 0, int y = 0) const noexcept -> void;

    private:
      auto createBoxedWindow(const std::optional<std::pair<int, int>> dimensions_xy) noexcept 
        -> std::unique_ptr<WINDOW, decltype(&delwin)>;
      
      std::unique_ptr<WINDOW, decltype(&delwin)> window_instance_ {createBoxedWindow()}; 
  };
}
