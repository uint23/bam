#include <stdlib.h>

#include <maus.h>

#include "common.h"
#include "grid.h"

Grid grid_init(int width, int height)
{
	Grid grid;

	int total = width*height;
	int size = total % 8 == 0 ?
	           ((width*height)/8) :
	           ((width*height)/8) + 1;

	grid.width = width;
	grid.height = height;
	grid.data = calloc(size, 1);
	if (grid.data == NULL)
		bamerr = ERR_GRID_ALLOC;

	return grid;
}

void grid_set_pixel(Grid* grid, int x, int y, int on)
{
	int n;
	int byte;
	int bit;
	unsigned char mask;

	if (!grid) {
		bamerr = ERR_GRID_INVALID;
		return;
	}

	if (x >= grid->width || x < 0 ||
	    y >= grid->height || y < 0) {
		bamerr = ERR_GRID_ACCESS_OOB;
		return;
	}

	n = y * grid->width + x;
	byte = n / 8;
	bit = n % 8;
	mask = 1 << bit;

	if (on)
		grid->data[byte] |= mask;
	else
		grid->data[byte] &= ~mask;
}

int grid_get_pixel(const Grid *grid, int x, int y)
{
	int n;
	int byte;
	int bit;
	unsigned char mask;

	if (!grid) {
		bamerr = ERR_GRID_INVALID;
		return -1;
	}

	if (x >= grid->width || x < 0 ||
	    y >= grid->height || y < 0) {
		bamerr = ERR_GRID_ACCESS_OOB;
		return -1;
	}

	n = y * grid->width + x;
	byte = n / 8;
	bit = n % 8;
	mask = 1 << bit;

	return (grid->data[byte] & mask) != 0;
}

