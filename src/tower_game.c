#include "tower_game.h"

#include <stdio.h>

#include "utils.h"

#define SCORE_GIVE_AMOUNT   (10)

int tower_game_init(struct tower_game *target)
{
	int num_rows = 0, num_columns = 0;
	struct tower *new_tower = NULL;

	while (TRUE) {
		printf("row, column values: ");

		scanf("%d%d", &num_rows, &num_columns);
		if (num_rows <= 0 || num_columns <= 0)
			printf("Invalid values! Try again.\n");
		else
			break;
	}

	new_tower = tower_new(num_rows, num_columns);
	if (new_tower == NULL) {
		return -1;
	}

	new_tower->owner = target;
	target->tower = new_tower;
	return 0;
}

int tower_game_loop(struct tower_game *target)
{
	int ret = 0;

	if (target == NULL)
		return TOWER_GAME_ERROR;

	ret = make_tower(target->tower);
	show_tower(target->tower);
	if (ret == MAKE_TOWER_CONTINUE)
		return TOWER_GAME_CONTINUE;

	return TOWER_GAME_FINISH;
}

int tower_game_give_score(struct tower_game *target)
{
	if (target == NULL) {
		return -1;
	}

	target->score += SCORE_GIVE_AMOUNT;
	return 0;
}

int tower_game_end(struct tower_game *target)
{
	if (target->tower != NULL) {
		tower_delete(target->tower);
		target->tower = NULL;
		return target->score;
	}

	return 0;
}

