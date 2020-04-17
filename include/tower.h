#ifndef _TOWER_GAME_TOWER_H
#define _TOWER_GAME_TOWER_H

#include "tower_game.h"

#define MAKE_TOWER_FINISH     (0)
#define MAKE_TOWER_CONTINUE   (-1)
#define MAKE_TOWER_ERROR      (-2)

struct column {
	struct row *owner;
	int value;
};

struct row {
	struct tower *owner;
	struct column **columns;
};

struct tower {
	struct tower_game *owner;

	int num_rows;
	int num_columns;

	struct row **rows;
};

struct tower *tower_new(int num_rows, int num_columns);
int tower_delete(struct tower *target);
int make_tower(struct tower *target);
int show_tower(struct tower *target);

#endif

