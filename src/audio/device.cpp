#include "audio/device.hpp"

Audio::Device::Device()
{
  // Automatically deduce sample rate.
  configuration_.sampleRate = 0;
}

auto Audio::Device::getConfiguration() const noexcept -> const ma_device_config & { return configuration_; }
