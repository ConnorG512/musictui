#include "audio/track-properties.hpp"

#include <stdexcept>

Audio::Properties::Properties(ma_sound& sound)
  : sound_{sound} 
{
  CreateProperties();
};

auto Audio::Properties::CreateProperties() -> void
{
  const auto result = ma_sound_get_data_format(
      &sound_, 
      nullptr, 
      &channels, 
      &sample_rate, 
      nullptr, 
      0 
    );

  if(result != MA_SUCCESS)
  {
    throw std::runtime_error("Failed to get track properties!");
  }
}
