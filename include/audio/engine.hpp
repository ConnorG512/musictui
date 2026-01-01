#pragma once 

#include <miniaudio/miniaudio.h>

namespace Audio 
{
  class Engine 
  {
    private:
      ma_engine engine_ {};

      auto CreateEngine() -> ma_engine;
      
      auto cref() const noexcept -> const ma_engine&;
      auto ref() noexcept -> ma_engine&;
    
    public:
      Engine();
      ~Engine();
  };
}
