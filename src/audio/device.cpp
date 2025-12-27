#include "audio/device.hpp"

Audio::Device::Device()
{
  // Automatically deduce sample rate.
  configuration_.sampleRate = 0;
}
