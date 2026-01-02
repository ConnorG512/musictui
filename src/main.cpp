#include "audio/engine.hpp"
#include "audio/playing-sound.hpp"
#include "audio/volume-handler.hpp"
#include "audio/playback.hpp"
#include "audio/track-properties.hpp"
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

  int current_track_index {2};
  Audio::PlayingSound current_track {audio_engine.ref(), track_list.at(current_track_index).c_str()};
  Audio::VolumeHandler volume_properties(current_track.ref(), 0.3);
  Audio::Properties current_track_properties{current_track.ref()};

  // Main Loop:
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  //start_color();
  
  refresh();
  UI::Window playback_window{
    std::optional<std::pair<int, int>>({getmaxx(stdscr), getmaxy(stdscr) / 8})};
  UI::Window contents_window{
    std::optional<std::pair<int, int>>(
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
      volume_properties.decreaseVolume(0.1);
    }
    if (character == KEY_F(4))
    {
      volume_properties.increaseVolume(0.1);
    }
    if (character == KEY_F(5))
    {
      Audio::Playback::seekBackward(
          current_track.ref(), current_track_properties.sample_rate);
    }
    if (character == KEY_F(6))
    {
      Audio::Playback::seekForward(
          current_track.ref(), current_track_properties.sample_rate);
    }
    if (character == KEY_F(7))
    {
    }
    if (character == 'k')
    {
      current_track_index += 1;
      if(current_track_index > track_list.size() - 1)
        current_track_index -= 1;
      current_track.resetSound(track_list.at(current_track_index).c_str());
      std::println("Current track: {}", track_list.at(current_track_index));
    }
    if (character == 'j')
    {
      current_track_index -= 1;
      if(current_track_index < 2)
        current_track_index += 1;
      current_track.resetSound(track_list.at(current_track_index).c_str());
      std::println("Current track: {}", track_list.at(current_track_index));
    }
    refresh();
  }

  endwin();
  return 0;
}
