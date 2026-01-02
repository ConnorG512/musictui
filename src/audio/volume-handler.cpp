#include "audio/volume-handler.hpp"

auto Audio::VolumeHandler::increaseVolume(Direction direction, float change_amount) noexcept -> float
{
  current_volume_ += change_amount; 
  if(current_volume_ > 1.0f)
    current_volume_ = 1.0f;

  ma_sound_set_volume(&sound_instance_, current_volume_);
  return current_volume_;
}

auto Audio::VolumeHandler::decreaseVolume(Direction direction, float change_amount) noexcept -> float
{
  current_volume_ -= change_amount; 
  if(current_volume_ < 0.0f)
    current_volume_ = 0.0f;
  
  ma_sound_set_volume(&sound_instance_, current_volume_);
  return current_volume_;
}

auto Audio::VolumeHandler::setVolume(float set_amount) noexcept -> float 
{
  current_volume_ = set_amount; 
  if(set_amount > 1.0f)
    set_amount = 1.0f;
  else if (set_amount < 0.0f)
    set_amount = 0.0f;

  ma_sound_set_volume(&sound_instance_, current_volume_);
  return current_volume_;
}
