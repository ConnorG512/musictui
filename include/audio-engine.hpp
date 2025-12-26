#pragma once

#include <memory>
#include <miniaudio/miniaudio.h>

namespace Audio 
{
class Engine 
{
  public:
    Engine();
    auto ptr() const noexcept -> const ma_engine*;

  private:
    ma_engine engine_ {}; 
};
}

