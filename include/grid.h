#ifndef GRID_H
#define GRID_H

typedef struct {
	int            width;
	int            height;
	unsigned char* data;
} Grid;

/* initialise a test grid size width by height */
Grid grid_init(int width, int height);

/* set pixel at (x, y) on/off */
void grid_set_pixel(Grid* grid, int x, int y, int on);

/* get pixel state at (x, y) */
int grid_get_pixel(const Grid* grid, int x, int y);

#endif /* GRID_H */

