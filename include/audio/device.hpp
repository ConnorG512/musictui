#pragma once

#include <miniaudio/miniaudio.h>

namespace Audio
{
class Device
{
public:
  Device();

  auto getConfiguration() const noexcept -> const ma_device_config &;

private:
  ma_device_config configuration_{ma_device_config_init(ma_device_type_playback)};
};
} // namespace Audio
