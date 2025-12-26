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

auto main(int argc, const char* argv[]) -> int
{
  // Get Music File
  if(argc != 2)
  {
    std::println("Invalid path to file!");
    return -1;
  }
  const char * music_path {argv[1]};
  
  Audio::Engine audio_engine{};
  TrackInstance playing_track (music_path, audio_engine);

  // Play sound
  ma_sound_start(&playing_track.ref());

  // Main Loop:
  initscr();
  keypad(stdscr, TRUE);

  printw("%s", std::format("playing:  {}", music_path).c_str());
  
  auto character {0};
  while((character = getch()) != 'q')
  {
    if(character == KEY_F(1))
      printw("F1 has been pressed!\n");
    
    refresh();
  }

  endwin();
  return 0;
}
