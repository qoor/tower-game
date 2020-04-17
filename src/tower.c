#include "tower.h"

#include <malloc.h>
#include <string.h>

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
	new_tower->rows = NULL;

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

