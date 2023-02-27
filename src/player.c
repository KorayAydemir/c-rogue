#include "../include/rogue.h"

Entity *createPlayer(Position start_pos) {
  Entity *newPlayer = calloc(1, sizeof(Entity));

  newPlayer->pos.y = start_pos.y;
  newPlayer->pos.x = start_pos.x;
  newPlayer->ch = '@';

  return newPlayer;
}

void handleInput(int input) {
  switch (input) {
  case 'k':
    player->pos.y--;
    break;
  case 'j':
    player->pos.y++;
    break;
  case 'h':
    player->pos.x--;
    break;
  case 'l':
    player->pos.x++;
    break;
  default:
    break;
  }
}
