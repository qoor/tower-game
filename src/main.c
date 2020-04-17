#include <stdio.h>

#include "tower.h"

#define TRUE 	(1)
#define FALSE 	(0)

int main (int argc, char **argv)
{
	struct tower *tower = NULL;
	int num_rows = 0, num_columns = 0;

	while (TRUE) {
		printf("row, column values: ");

		scanf("%d%d", &num_rows, &num_columns);
		if (num_rows <= 0 || num_columns <= 0)
			printf("Invalid values! Try again.\n");
		else
			break;
	}

	tower = tower_new(num_rows, num_columns);
	if (tower == NULL) {
		printf("Program error!\n");
		return 0;
	}

	return 0;
}

