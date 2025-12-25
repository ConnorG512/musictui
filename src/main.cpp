#include <ncurses.h>
#include <format>
#include <string>
#include <print>
#include <cassert>
#include <AL/al.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

auto main(int argc, const char* argv[]) -> int
{
  // Get Music File
  if(argc < 2)
  {
    std::println("No music path provided!");
    endwin();
    return -1;
  }

  const char * music_path {argv[1]};
  
  // Open file:
  const auto song_open {open(music_path, O_RDONLY)};
  if (song_open == -1)
  {
    std::println("No music path provided! Error: {}", strerror(errno));
    endwin();
    return -1;
  }
  
  // Main Loop:
  initscr();
  keypad(stdscr, TRUE);

  printw("%s", "MusicTUI!");
  
  
  auto character {0};
  while((character = getch()) != 'q')
  {
    if(character == KEY_F(1))
      printw("F1 has been pressed!\n");
    
    refresh();
  }

  endwin();

  close(song_open);
  return 0;
}
