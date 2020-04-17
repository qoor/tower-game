#include "tower.h"

#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <string.h>

static int tower_new_value(struct tower *target, int row, int column);
static int tower_overlap_check(struct tower *target, int row, int column);
static struct row *row_new(int num_columns);
static int row_delete(struct row *target);
static struct column *column_new();
static int column_delete(struct column *target);

struct tower *tower_new(int num_rows, int num_columns)
{
	int i;
	struct tower *new_tower = NULL;

	if (num_rows <= 0 || num_columns <= 0)
		return NULL;

	new_tower = malloc(sizeof(struct tower));
	if (new_tower == NULL)
		return NULL;

	new_tower->rows = malloc(sizeof(struct rows *) * num_rows);
	if (new_tower->rows == NULL) {
		free(new_tower);
		return NULL;
	}
	
	memset(new_tower->rows, 0x00, sizeof(struct rows *) * num_rows);
	new_tower->num_rows = num_rows;
	new_tower->num_columns = num_columns;

	for (i = 0; i < num_rows; ++i) {
		new_tower->rows[i] = row_new(num_columns);
		if (new_tower->rows == NULL) {
			tower_delete(new_tower);
			new_tower = NULL;
			break;
		} else {
			new_tower->rows[i]->owner = new_tower;
		}
	}

	srand(time(NULL));

	return new_tower;
}

int tower_delete(struct tower *target)
{
	int i;
	int ret = 0;

	if (target == NULL)
		return -1;

	for (i = 0; i < target->num_rows; ++i) {
		ret = row_delete(target->rows[i]);
		if (ret == 0)
			target->rows[i] = NULL;
	}

	free(target);
	return 0;
}

int tower_get_empty_row(struct tower* target, int column)
{
	int i;

	for (i = 0; i < target->num_rows; ++i) {
		if (target->rows[i]->columns[column]->value == 0) {
			return i;
		}
	}

	return -1;
}

int tower_new_value(struct tower *target, int row, int column)
{
	int new_value = 0;

	new_value = (rand() % MAX_RANDOM_VALUE) + 1;

	target->rows[row]->columns[column]->value = new_value;
	return new_value;
}

int tower_overlap_check(struct tower *target, int row, int column)
{
	int current_value = 0;
	int under_row_value = 0;

	if (row <= 0)
		return -1;

	current_value = target->rows[row]->columns[column]->value;
	under_row_value = target->rows[row - 1]->columns[column]->value;

	if (current_value == under_row_value) {
		target->rows[row]->columns[column]->value = 0;
		target->rows[row - 1]->columns[column]->value = 0;

		tower_game_give_score(target->owner);
	}

	return 0;
}

int make_tower(struct tower *target)
{
	int current_column = 0;
	int num_columns = 0;
	int empty_row = 0;
	int status = MAKE_TOWER_CONTINUE;

	if (target == NULL)
		return MAKE_TOWER_ERROR;


	num_columns = target->num_columns;

	while (current_column < num_columns) {
		empty_row = tower_get_empty_row(target, current_column);
		if (empty_row == -1) {
			status = MAKE_TOWER_FINISH;
			break;
		}

		tower_new_value(target, empty_row, current_column);
		tower_overlap_check(target, empty_row, current_column);

		++current_column;
	}

	return status;
}

int show_tower(struct tower *target)
{
	int i, j;

	if (target == NULL)
		return -1;

	for (i = target->num_rows - 1; i >= 0; --i) {
		for (j = 0; j < target->num_columns; ++j)
			printf("%d\t", target->rows[i]->columns[j]->value);

		printf("\n");
	}

	printf("Score: %d\n", target->owner->score);
	return 0;
}

struct row *row_new(int num_columns)
{
	int i;
	struct row *new_row = NULL;

	new_row = malloc(sizeof(struct row));
	if (new_row == NULL)
		return NULL;

	new_row->columns = malloc(sizeof(struct column *) * num_columns);
	if (new_row->columns == NULL) {
		free(new_row);
		return NULL;
	}

	memset(new_row->columns, 0x00, sizeof(struct column *) * num_columns);
	for (i = 0; i < num_columns; ++i) {
		new_row->columns[i] = column_new();
		if (new_row->columns[i] == NULL) {
			free(new_row->columns);
			free(new_row);
			return NULL;
		} else {
			new_row->columns[i]->owner = new_row;
		}
	}

	return new_row;
}

int row_delete(struct row *target)
{
	int i;
	int ret = 0;

	if (target == NULL)
		return -1;

	for (i = 0; i < target->owner->num_columns; ++i) {
		ret = column_delete(target->columns[i]);
		if (ret == 0)
			target->columns[i] = NULL;
	}

	return 0;
}

struct column *column_new()
{
	struct column *new_column = NULL;

	new_column = malloc(sizeof(struct column));
	if (new_column == NULL)
		return NULL;

	new_column->owner = NULL;
	new_column->value = 0;

	return new_column;
}

int column_delete(struct column *target)
{
	if (target == NULL)
		return -1;

	free(target);
	return 0;
}

