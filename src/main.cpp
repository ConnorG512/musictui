#include "audio/engine.hpp"
#include "audio/volume.hpp"
#include "track_instance.hpp"

#include <ncurses.h>
#include <format>
#include <string>
#include <print>
#include <cassert>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <locale.h>
#include <cwchar>

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
  
  const char * music_path {argv[1]};
  
  wchar_t wide_buffer [2048];
  mbstowcs(wide_buffer, std::format("playing:  {}", music_path).c_str(), 2048);

  Audio::Engine audio_engine{};
  TrackInstance playing_track (music_path, audio_engine);

  // Play sound
  ma_sound_start(&playing_track.ref());

  // Main Loop:
  initscr();
  keypad(stdscr, TRUE);

  mvaddwstr(0, 0, wide_buffer);
  
  auto character {0};
  while((character = getch()) != 'q')
  {
    if(character == KEY_F(1))
    {
      mvprintw(1, 0, "%s", std::format("Volume: {:3.2f}%", playing_track.track_volume.decreaseVolume()).c_str());
    }
    if(character == KEY_F(2))
    {
      mvprintw(1, 0, "%s", std::format("Volume: {:3.2f}%", playing_track.track_volume.increaseVolume()).c_str());
    }
    refresh();
  }

  endwin();
  return 0;
}
