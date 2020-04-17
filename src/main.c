#include <stdio.h>

#include "tower_game.h"

void error_message();

int main (int argc, char **argv)
{
	struct tower_game game = { 0, };
	int ret = 0;

	ret = tower_game_init(&game);
	if (ret != 0) {
		error_message();
		return 0;
	}

	do {
		ret = tower_game_loop(&game);
	} while (ret == TOWER_GAME_CONTINUE);

	tower_game_end(&game);

	return 0;
}

void error_message()
{
	printf("Program error!\n");
}

