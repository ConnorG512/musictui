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
  
  if(argv[1] == nullptr)
    throw std::runtime_error("No music path provided!");
  
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
