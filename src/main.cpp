#include "audio/device.hpp"
#include "audio/engine.hpp"
#include "audio/volume.hpp"
#include "track_instance.hpp"
#include "ui/window.hpp"
#include "ui/text-output.hpp"

#include <array>
#include <cassert>
#include <cwchar>
#include <format>
#include <locale.h>
#include <ncurses.h>
#include <print>
#include <string>
#include <sys/mman.h>
#include <array>

auto main(int argc, const char *argv[]) -> int
{
  // Get Music File
  if (argc != 2)
  {
    std::println("Invalid path to file!");
    return -1;
  }

  // Enabling all localisation
  setlocale(LC_ALL, "");
  start_color();

  const std::string music_path{argv[1]};

  Audio::Device device{};
  Audio::Engine audio_engine{};
  TrackInstance playing_track(music_path.c_str(), audio_engine);

  // Play sound
  ma_sound_start(&playing_track.ref());

  // Main Loop:
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  
  refresh();
  UI::Window playback_window{std::optional<std::pair<int, int>>({getmaxx(stdscr), getmaxy(stdscr) / 8})};
  UI::Window contents_window{std::optional<std::pair<int, int>>(
      {getmaxx(stdscr), getmaxy(stdscr) / 8 * 7}),
      {0, getmaxy(stdscr) / 8}
  };
  
  std::array<std::pair<int,int>, 2> positions {{ {1,1} }};
  std::array<const char*, 1> messages {"Now playing: "};
  UI::Text::drawStringsToScreen(
      contents_window.ptr(),
      messages, 
      std::span<std::pair<int,int>>(positions));

  auto character{0};
  while ((character = getch()) != 'q')
  {
    if (character == KEY_F(1))
    {
      playing_track.track_volume.decreaseVolume();
    }
    if (character == KEY_F(2))
    {
      playing_track.track_volume.increaseVolume();
    }
    if (character == KEY_F(3))
    {
      playing_track.pauseTrack();
    }
    if (character == KEY_F(4))
    {
      playing_track.playTrack();
    }
    if (character == KEY_F(5))
    {
      playing_track.seekBackward();
    }
    if (character == KEY_F(6))
    {
      playing_track.seekForward();
    }
    if (character == KEY_F(7))
    {
      playing_track.stopTrack();
    }
    refresh();
  }

  endwin();
  return 0;
}
