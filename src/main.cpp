#include "audio/device.hpp"
#include "audio/engine.hpp"
#include "audio/volume.hpp"
#include "track_instance.hpp"
#include "ui/window.hpp"

#include <array>
#include <cassert>
#include <cwchar>
#include <format>
#include <locale.h>
#include <ncurses.h>
#include <print>
#include <string>
#include <sys/mman.h>

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

  refresh();
  UI::Window playback_window{std::optional<std::pair<int, int>>({getmaxx(stdscr), getmaxy(stdscr) / 8})};

  playback_window.drawTextToWindow("Now playing:", 1, 1);
  playback_window.drawTextToWindow(music_path.c_str(), 1, 2);
  playback_window.drawTextToWindow(std::string{"Volume Down: F1"}.c_str(), 1, 3);
  playback_window.drawTextToWindow(std::string{"Volume Up: F2"}.c_str(), 1, 4);
  playback_window.drawTextToWindow(std::string{"Pause: F3"}.c_str(), 1, 5);
  playback_window.drawTextToWindow(std::string{"Play: F4"}.c_str(), 1, 6);
  playback_window.drawTextToWindow(std::string{"Seek Backward: F5"}.c_str(), 1, 7);
  playback_window.drawTextToWindow(std::string{"Seek Forward: F6"}.c_str(), 1, 8);
  playback_window.drawTextToWindow(std::string{"Stop: F7"}.c_str(), 1, 9);

  UI::Window contents_window{std::optional<std::pair<int, int>>(
      {getmaxx(stdscr), getmaxy(stdscr) / 8 * 7}),
      {0, getmaxy(stdscr) / 8}
  };
  
  auto character{0};
  while ((character = getch()) != 'q')
  {
    if (character == KEY_F(1))
    {
      playback_window.drawTextToWindow(
          std::format("Volume: {:3.2f}%", (playing_track.track_volume.decreaseVolume()) * 100).c_str(), 1, 10);
    }
    if (character == KEY_F(2))
    {
      playback_window.drawTextToWindow(
          std::format("Volume: {:3.2f}%", (playing_track.track_volume.increaseVolume()) * 100).c_str(), 1, 10);
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
