#include "../include/rogue.h"

Entity *createPlayer(Position start_pos) {
  Entity *newPlayer = calloc(1, sizeof(Entity));

  newPlayer->pos.y = start_pos.y;
  newPlayer->pos.x = start_pos.x;
  newPlayer->ch = '@';

  return newPlayer;
}

void handleInput(int input) {
  Position newPos = {player->pos.y, player->pos.x};

  switch (input) {
  case 'k':
    newPos.y--;
    break;
  case 'j':
    newPos.y++;
    break;
  case 'h':
    newPos.x--;
    break;
  case 'l':
    newPos.x++;
    break;
  default:
    break;
  }
  movePlayer(newPos);
}

void movePlayer(Position newPos) {
  if (map[newPos.y][newPos.x].walkable) {
    player->pos.y = newPos.y;
    player->pos.x = newPos.x;
  }
}
