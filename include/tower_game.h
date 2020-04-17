#ifndef _TOWER_GAME_TOWER_GAME_H
#define _TOWER_GAME_TOWER_GAME_H

#include "tower.h"

#define TOWER_GAME_FINISH   (0)
#define TOWER_GAME_CONTINUE (-1)
#define TOWER_GAME_ERROR    (-2)


#define MAX_RANDOM_VALUE    (9)

struct tower_game {
  struct tower *tower;
  int score;
};

int tower_game_init(struct tower_game *target);
int tower_game_loop(struct tower_game *target);
int tower_game_give_score(struct tower_game *target);
int tower_game_end(struct tower_game *target);

#endif
