#include <ncurses.h>
#include <format>
#include <string>
#include <print>
#include <cassert>
#include <AL/al.h>

auto main(int argc, const char* argv[]) -> int
{
  initscr();
  keypad(stdscr, TRUE);

  printw("%s", "MusicTUI!");
  
  if(argc < 2)
  {
    std::println("No music path provided!");
    endwin();
    return -1;
  }
  
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
