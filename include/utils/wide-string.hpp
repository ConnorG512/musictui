#pragma once

#include <cstdint>
#include <array>
#include <span>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <concepts>

namespace Utils 
{
  template<typename String, std::uint32_t buffer_size>
  requires std::same_as<String, const char*> || std::same_as<String, const wchar_t*>
  class WideString
  {
    public: 
     constexpr explicit WideString(std::array<wchar_t, buffer_size> input_text)
        : buffer_{writeBuffer(input_text)} {}

      auto getData() const noexcept -> std::span<const wchar_t>
      {
        return buffer_;
      }

      auto writeBuffer(std::array<String, buffer_size> input_text) -> void
      {
        if constexpr (std::same_as<String, const char*>)
        {
          mbstowcs(buffer_, input_text.data(), buffer_size);
        }
        if(input_text.size() > buffer_size)
          throw std::runtime_error("buffersize too big!");
        
        std::ranges::copy(buffer_.data(), input_text, sizeof(buffer_));
      }

    private:
      std::array<wchar_t, buffer_size> buffer_{};
  };
}
