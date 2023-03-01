#include "../include/rogue.h"
#include <stdlib.h>

Tile **createMapTiles(void) {
  Tile **tiles = calloc(MAP_HEIGHT, sizeof(Tile *));

  for (int y = 0; y < MAP_HEIGHT; y++) {
    tiles[y] = calloc(MAP_WIDTH, sizeof(Tile));

    for (int x = 0; x < MAP_WIDTH; x++) {
      tiles[y][x].ch = '#';
      tiles[y][x].walkable = false;
    }
  }

  return tiles;
}

void freeMap(void) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    free(map[y]);
  }
  free(map);
}

Position setupMap(void) {
  Position start_pos;
  // generate random rooms
  const int MAX_ROOMS = 1;
  const int MIN_ROOMS = 1;
  const int MAX_HEIGHT = 10;
  const int MIN_HEIGHT = 5;
  const int MAX_WIDTH = 18;
  const int MIN_WIDTH = 9;

  int n_rooms = (rand() % (MAX_ROOMS - MIN_ROOMS + 1)) + MIN_ROOMS;

  for (int i = 0; i < n_rooms; i++) {
    int y, x, height, width;
    y = (rand() % (MAP_HEIGHT - MAX_HEIGHT)) + 1;
    x = (rand() % (MAP_WIDTH - MAX_WIDTH)) + 1;
    height = (rand() % (MAX_HEIGHT - MIN_HEIGHT)) + MIN_HEIGHT;
    width = (rand() % (MAX_WIDTH - MIN_WIDTH)) + MIN_WIDTH;
    Room room = createRoom(y, x, height, width);
    addRoomToMap(room);

    if (i == 0) {
      Position start_pos = {y, x};
      printf("%d,%d -- ", start_pos.y, start_pos.x); // expected values
    }
    printf("%d,%d -- ", start_pos.y, start_pos.x); // unexpected negative values
  }
  printf("%d,%d", start_pos.y, start_pos.x); // same values as above

  return start_pos; // returns neither of the above to main. Returns a positive
                    // number in reasonable range, but still a different number.
};

Room createRoom(int y, int x, int height, int width) {
  Room newRoom;

  newRoom.pos.y = y;
  newRoom.pos.x = x;
  newRoom.height = height;
  newRoom.width = width;
  newRoom.center.y = y + (int)(height / 2);
  newRoom.center.x = x + (int)(width / 2);

  return newRoom;
}

void addRoomToMap(Room room) {
  for (int y = room.pos.y; y < room.pos.y + room.height; y++) {
    for (int x = room.pos.x; x < room.pos.x + room.width; x++) {
      map[y][x].ch = '.';
      map[y][x].walkable = true;
    }
  }
}
