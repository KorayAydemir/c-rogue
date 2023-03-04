#include "../include/rogue.h"
#include <curses.h>
#include <stdlib.h>

Tile **createMapTiles(void) {
  Tile **tiles = calloc(MAP_HEIGHT, sizeof(Tile *));

  for (int y = 0; y < MAP_HEIGHT; y++) {
    tiles[y] = calloc(MAP_WIDTH, sizeof(Tile));

    for (int x = 0; x < MAP_WIDTH; x++) {
      tiles[y][x].ch = '#';
      tiles[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
      tiles[y][x].walkable = false;

      tiles[y][x].transparent = false;
      tiles[y][x].visible = false;
      tiles[y][x].seen = false;
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
  const int MAX_ROOMS = 10;
  const int MIN_ROOMS = 9;
  const int MAX_HEIGHT = 10;
  const int MIN_HEIGHT = 5;
  const int MAX_WIDTH = 18;
  const int MIN_WIDTH = 9;

  int n_rooms = (rand() % (MAX_ROOMS - MIN_ROOMS + 1)) + MIN_ROOMS;

  Room rooms[n_rooms];
  int y, x;
  int rooms_counter;
  for (int i = 0; i < n_rooms; i++) {
    int height, width;
    y = (rand() % (MAP_HEIGHT - MAX_HEIGHT)) + 1;
    x = (rand() % (MAP_WIDTH - MAX_WIDTH)) + 1;
    height = (rand() % (MAX_HEIGHT - MIN_HEIGHT)) + MIN_HEIGHT;
    width = (rand() % (MAX_WIDTH - MIN_WIDTH)) + MIN_WIDTH;

    if (!roomOverlaps(y, x, height, width, i, rooms)) {
      rooms[rooms_counter] = createRoom(y, x, height, width);
      addRoomToMap(rooms[rooms_counter]);
      if (rooms_counter > 0) {
        connectRoomCenters(rooms[rooms_counter - 1].center,
                           rooms[rooms_counter].center);
      }
      rooms_counter++;
    }
  }
  start_pos.x = rooms[0].center.x;
  start_pos.y = rooms[0].center.y;

  return start_pos;
}

void connectRoomCenters(Position centerOne, Position centerTwo) {
  Position temp;
  temp.x = centerOne.x;
  temp.y = centerOne.y;

  while (true) {
    if (abs((temp.x - 1) - centerTwo.x) < abs(temp.x - centerTwo.x))
      temp.x--;
    else if (abs((temp.x + 1) - centerTwo.x) < abs(temp.x - centerTwo.x))
      temp.x++;
    else if (abs((temp.y + 1) - centerTwo.y) < abs(temp.y - centerTwo.y))
      temp.y++;
    else if (abs((temp.y - 1) - centerTwo.y) < abs(temp.y - centerTwo.y))
      temp.y--;
    else
      break;

    map[temp.y][temp.x].ch = '.';
    map[temp.y][temp.x].walkable = true;
    map[temp.y][temp.x].transparent = true;
  }
}

bool roomOverlaps(int y, int x, int height, int width, int rooms_counter,
                  Room rooms[]) {
  for (int i = 0; i < rooms_counter; i++) {
    if (x >= rooms[i].pos.x + rooms[i].width || rooms[i].pos.x >= x + width) {
      continue;
    }
    if (y + height <= rooms[i].pos.y || rooms[i].pos.y + rooms[i].height <= y) {
      continue;
    }

    return true;
  }

  return false;
}

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
      map[y][x].transparent = true;
    }
  }
}
