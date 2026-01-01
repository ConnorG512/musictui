#include "audio/engine.hpp"
#include "audio/playing-sound.hpp"
#include "audio/volume.hpp"
#include "audio/playback.hpp"
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
  Audio::Engine audio_engine{};
  Audio::PlayingSound current_track {audio_engine.ref(), track_list.at(2).c_str()};
  Audio::setVolume(current_track.ref(), 0.3);

  
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
      Audio::Playback::startPlayback(current_track.ref());
    }
    if (character == KEY_F(2))
    {
      Audio::Playback::stopPlayback(current_track.ref());
    }
    if (character == KEY_F(3))
    {
    }
    if (character == KEY_F(4))
    {
    }
    if (character == KEY_F(5))
    {
    }
    if (character == KEY_F(6))
    {
    }
    if (character == KEY_F(7))
    {
    }
    if (character == 'k')
    {
    }
    if (character == 'j')
    {
    }
    refresh();
  }

  endwin();
  return 0;
}
