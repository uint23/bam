#include <stdlib.h>

#include <maus.h>

#include "grid.h"

Grid grid_init(int width, int height)
{
	Grid grid;

	grid.width = width;
	grid.height = height;
	grid.data = malloc(width * height);
	if (grid.data == NULL)
		maus_die("Failed to malloc grid data");

	return grid;
}

