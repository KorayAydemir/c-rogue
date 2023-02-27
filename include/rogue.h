#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>

typedef struct Position {
  int y;
  int x;

} Position;

typedef struct Entity {
  Position pos;
  char ch;
} Entity;

// engine.c functions
void cursesSetup(void);
void gameLoop(void);
void closeGame(void);

Entity *createPlayer(Position start_pos);
void handleInput(int input);

extern Entity *player;

#endif
