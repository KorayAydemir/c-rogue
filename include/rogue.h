#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

// color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2

typedef struct Position {
  int y;
  int x;

} Position;

typedef struct Entity {
  Position pos;
  char ch;
  int color;
} Entity;
extern Entity *player;

typedef struct Tile {
  int color;
  char ch;
  bool walkable;
  bool transparent;
  bool visible;
  bool seen;
} Tile;
extern Tile **map;

typedef struct Room {
  int height;
  int width;
  Position pos;
  Position center;
} Room;

// engine.c functions
bool cursesSetup(void);
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
bool roomOverlaps(int y, int x, int height, int width, int roomsCount,
                  Room rooms[]);
void connectRoomCenters(Position centerOne, Position centerTwo);

// draw.c functions
void drawMap(void);
void drawEntity(Entity *entity);
void drawEverything(void);

// player.c functions
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;

// room.c functions
Room createRoom(int y, int x, int height, int width);
void addRoomToMap(Room room);

// fov.c functions
bool isInMap(int y, int x);
void makeFOV(Entity *player);
void clearFOV(Entity *player);
int getDistance(Position origin, Position target);
bool lineOfSight(Position origin, Position target);
int getSign(int a);

#endif
