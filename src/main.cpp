#include <ncurses.h>

auto main() -> int
{
  initscr();
  printw("Hello Ncurses!");
  refresh();
  getch();
  endwin();

  return 0;
}
