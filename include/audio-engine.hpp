#pragma once

#include <memory>
#include <miniaudio/miniaudio.h>

namespace Audio 
{
class Engine 
{
  public:
    Engine();

  private:
    std::unique_ptr<ma_engine, decltype(&ma_engine_uninit)> engine_ {nullptr, &ma_engine_uninit}; 
};
}

