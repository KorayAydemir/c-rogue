#include "../include/rogue.h"

void cursesSetup(void) {
  initscr();
  noecho();
  curs_set(0);
}
