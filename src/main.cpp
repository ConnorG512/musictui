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
#include <miniaudio/miniaudio.h>

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
  
  // Mini Audio
  ma_engine engine{};
  ma_result result {ma_engine_init(nullptr, &engine)};
  if(result != MA_SUCCESS)
  {
    std::println("Failed to create miniaudio result!");
    endwin();
    return -1;
  }

  // Main Loop:
  initscr();
  keypad(stdscr, TRUE);

  printw("%s", std::format("playing:  {}", argv[1]).c_str());
  
  auto character {0};
  while((character = getch()) != 'q')
  {
    if(character == KEY_F(1))
      printw("F1 has been pressed!\n");
    
    refresh();
  }
  
  ma_engine_uninit(&engine);
  endwin();
  return 0;
}
