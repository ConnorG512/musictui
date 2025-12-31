#include "audio/device.hpp"
#include "audio/engine.hpp"
#include "audio/volume.hpp"
#include "track_instance.hpp"
#include "ui/window.hpp"
#include "ui/text-output.hpp"
#include "read-directory.hpp"

#include <array>
#include <cassert>
#include <cwchar>
#include <format>
#include <locale.h>
#include <ncurses.h>
#include <string>
#include <sys/mman.h>
#include <array>
#include <print>

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
  start_color();
  
  refresh();
  UI::Window playback_window{std::optional<std::pair<int, int>>({getmaxx(stdscr), getmaxy(stdscr) / 8})};
  UI::Window contents_window{std::optional<std::pair<int, int>>(
      {getmaxx(stdscr), getmaxy(stdscr) / 8 * 7}),
      {0, getmaxy(stdscr) / 8}
  };
  
  constexpr UI::Text::Properties<7> user_controls
  {
    .messages = {
      "Decrease Volume: F1",
      "Increase Volume: F2",
      "Pause: F3",
      "Play: F4",
      "Seek Backward: F5",
      "Seek Forward: F6",
      "Stop: F7",
    },
    .xy_positions = {{
      {1,10},
      {1,11},
      {1,12},
      {1,13},
      {1,14},
      {1,15},
      {1,16}
    }},
    .color = std::nullopt,
  };
  UI::Text::drawStringsToScreen(contents_window.ptr(), user_controls);

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
