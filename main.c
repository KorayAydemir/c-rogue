#include <curses.h>
#include <ncurses.h>
#include <stdio.h>

int main() {
  initscr();
  noecho();
  curs_set(0);

  while (getch() != 'q') {
    mvaddch(10, 20, '@');
  }

  endwin();
  return 0;
}
