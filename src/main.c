#include "../include/rogue.h"
#include <stdio.h>

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Entity *player;
Tile **map;

int main(void) {
  cursesSetup();

  map = createMapTiles();
  Position start_pos = setupMap();
  player = createPlayer(start_pos);

  gameLoop();

  closeGame();

  return 0;
}
