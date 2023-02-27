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
extern Entity *player;

typedef struct Tile {
  char ch;
  bool walkable;
} Tile;
extern Tile **map;

// engine.c functions
void cursesSetup(void);
void gameLoop(void);
void closeGame(void);

// main.c functions
Entity *createPlayer(Position start_pos);
void handleInput(int input);

void movePlayer(Position newPos);

// map.c functions
Tile **createMapTiles(void);
void freeMap(void);
Position setupMap(void);

// draw.c functions
void drawMap(void);
void drawEntity(Entity *entity);
void drawEverything(void);

// player.c functions

extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;

#endif
