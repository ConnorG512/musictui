#pragma once

#include <cstdint>
#include <array>
#include <span>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iostream>

namespace Utils 
{
  template <std::uint32_t buffer_size>
  class WideString
  {
    public: 
     consteval explicit WideString(std::array<wchar_t, buffer_size> input_text)
        : buffer_{writeBuffer(input_text)} {}

      auto getData() const noexcept -> std::span<const wchar_t>
      {
        return buffer_;
      }
      auto writeBuffer(std::array<wchar_t, buffer_size> input_text) -> void
      {
        if(input_text.size() > buffer_size)
          throw std::runtime_error("buffersize too big!");
        
        std::ranges::copy(buffer_.data(), input_text, sizeof(buffer_));
      }

    private:
      std::array<wchar_t, buffer_size> buffer_{};
  };
}
