#include "audio/engine.hpp"
#include "audio/volume.hpp"

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
  ma_sound playing_track{};
  ma_sound_init_from_file(
      audio_engine.ptr(), 
      music_path, 
      0, 
      nullptr, 
      nullptr, 
      &playing_track 
  );
  Audio::Volume volume_instance{playing_track};
  ma_engine_play_sound(audio_engine.ptr(), music_path, nullptr);
  
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
  
  ma_sound_uninit(&playing_track);
  endwin();
  return 0;
}
