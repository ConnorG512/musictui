#include "audio/engine.hpp"
#include "audio/volume.hpp"
#include "audio/device.hpp"
#include "track_instance.hpp"
#include "ui/window.hpp"

#include <ncurses.h>
#include <format>
#include <string>
#include <print>
#include <cassert>
#include <sys/mman.h>
#include <locale.h>
#include <cwchar>
#include <array>

auto main(int argc, const char* argv[]) -> int
{
  // Get Music File
  if(argc != 2)
  {
    std::println("Invalid path to file!");
    return -1;
  }
  
  // Enabling all localisation
  setlocale(LC_ALL, "");
  
  const std::string music_path {argv[1]};
  
  Audio::Device device {};
  Audio::Engine audio_engine {};
  TrackInstance playing_track (music_path.c_str(), audio_engine);
  
  // Play sound
  ma_sound_start(&playing_track.ref());

  // Main Loop:
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  
  refresh();
  UI::Window app_window{100, 20};
  app_window.drawTextToWindow("Now playing:", 1, 1);
  app_window.drawTextToWindow(music_path.c_str(), 1, 2);
  app_window.drawTextToWindow(std::string{"Volume Down: F1"}.c_str(), 1, 3);
  app_window.drawTextToWindow(std::string{"Volume Down: F2"}.c_str(), 1, 4);
  app_window.drawTextToWindow(std::string{"Pause: F3"}.c_str(), 1, 5);
  app_window.drawTextToWindow(std::string{"Play: F4"}.c_str(), 1, 6);
  app_window.drawTextToWindow(std::string{"Seek Backward: F5"}.c_str(), 1, 7);
  app_window.drawTextToWindow(std::string{"Seek Forward: F6"}.c_str(), 1, 8);
  app_window.drawTextToWindow(std::string{"Stop: F7"}.c_str(), 1, 9);

  auto character {0};
  while((character = getch()) != 'q')
  {
    if(character == KEY_F(1))
    {
      app_window.drawTextToWindow(std::format("Volume: {:3.2f}%", (playing_track.track_volume.decreaseVolume()) * 100).c_str(), 1, 10);
    }
    if(character == KEY_F(2))
    {
      app_window.drawTextToWindow(std::format("Volume: {:3.2f}%", (playing_track.track_volume.increaseVolume()) * 100).c_str(), 1, 10);
    }
    if(character == KEY_F(3))
    {
      playing_track.pauseTrack();
    }
    if(character == KEY_F(4))
    {
      playing_track.playTrack();
    }
    if(character == KEY_F(5))
    {
      playing_track.seekBackward();
    }
    if(character == KEY_F(6))
    {
      playing_track.seekForward();
    }
    if(character == KEY_F(7))
    {
      playing_track.stopTrack();
    }
    refresh();
  }

  endwin();
  return 0;
}
