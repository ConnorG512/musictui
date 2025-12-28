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

struct ScreenPos {
  int x {0};
  int y {0};
};

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
  UI::Window app_window{30, 20};

  for(const auto& ch : std::string_view{"Playing:\n"})
  {
    addch(ch | A_BOLD | A_UNDERLINE);
  }

  printw("%s", music_path.c_str());
  
  auto character {0};
  while((character = getch()) != 'q')
  {
    if(character == KEY_F(1))
    {
      mvprintw(1, 0, "%s", std::format("Volume: {:3.2f}%", (playing_track.track_volume.decreaseVolume()) * 100).c_str());
    }
    if(character == KEY_F(2))
    {
      mvprintw(1, 0, "%s", std::format("Volume: {:3.2f}%", (playing_track.track_volume.increaseVolume()) * 100).c_str());
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
