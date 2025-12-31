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
#include <stdexcept>

auto main(int argc, const char *argv[]) -> int
{
  // Get Music File
  if (argc != 2)
    std::runtime_error("Invalid path to file!");

  // Enabling all localisation
  setlocale(LC_ALL, "");
  
  std::vector<std::string> track_list{};
  track_list.reserve(3);

  // Directory
  Directory opened_directory{argv[1]};
  
  auto found_tracks {opened_directory.GetDirectoryContents()};
  if(found_tracks.empty())
    std::runtime_error("Song list empty!");

  for(const auto track : found_tracks)
  {
    track_list.emplace_back(std::format("{}{}", argv[1], track)); 
  }

  // Audio
  Audio::Device device{};
  Audio::Engine audio_engine{};

  TrackInstance playing_track(track_list.at(3).c_str(), audio_engine);

  // Play sound
  ma_sound_start(&playing_track.ref());
  
  // Main Loop:
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  //start_color();
  
  refresh();
  UI::Window playback_window{std::optional<std::pair<int, int>>({getmaxx(stdscr), getmaxy(stdscr) / 8})};
  UI::Window contents_window{std::optional<std::pair<int, int>>(
      {getmaxx(stdscr), getmaxy(stdscr) / 8 * 7}),
      {0, getmaxy(stdscr) / 8}
  };
  
  UI::Text::drawVerticalStringList(contents_window.ptr(), track_list, {1,10});
  
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
