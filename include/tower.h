#ifndef _TOWER_GAME_TOWER_H
#define _TOWER_GAME_TOWER_H

struct column {
  struct row *owner;
  int value;
};

struct row {
  struct tower *owner;
  struct column **columns;
};

struct tower {
  int num_rows;
  int num_columns;

  struct row **rows;
};

struct tower *tower_new(int num_rows, int num_columns);
int tower_delete(struct tower *target);

#endif

