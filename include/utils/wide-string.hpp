#pragma once

#include <cstdint>
#include <array>
#include <span>

namespace Utils 
{
  template <std::uint32_t buffer_size>
  class WideString
  {
    public: 
      auto getData() const noexcept -> std::span<const wchar_t>
      {
        return buffer_;
      }
    private:
      std::array<wchar_t, buffer_size> buffer_{};
  };
}
