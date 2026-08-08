#ifndef GRID_H
#define GRID_H

typedef struct {
	int            width;
	int            height;
	unsigned char* data;
} Grid;

/* initialise a test grid size width by height */
Grid grid_init(int width, int height);

#endif /* GRID_H */

