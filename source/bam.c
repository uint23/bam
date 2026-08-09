#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <maus.h>

#include "common.h"
#include "events.h"
#include "grid.h"

static void run(void);
static void setup(void);
static void set_pixel(unsigned x, unsigned y, uint32_t col);

Bam bam = { 0 };
ErrorType bamerr = ERR_OK;
static Maus* ctx = NULL;
static MausEvent maus_event;
static int running = 0;

Grid test_grid = { 0 };

static MausColor col_white = { 255, 255, 255, 255 };

static void run(void)
{
	int x;
	int y;

	running = 1;
	while (running) {
		maus_event_wait(ctx, &maus_event);
		event_handler[maus_event.type](&bam);
		maus_clear(ctx, col_white);

		/* draw grid */
		for (y = 0; y < test_grid.height; y++) {
			for (x = 0; x < test_grid.width; x++) {
				if (grid_get_pixel(&test_grid, x, y))
					set_pixel(x, y, 0xFF000000);
			}
		}

		maus_present(ctx);
	}
}

static void setup(void)
{
	ctx = maus_init("bam", 10, 10, 800, 600);
	if (!ctx)
		maus_die("Failed to initialise maus context");

	if (!maus_create_window(ctx))
		maus_die("Failed to create maus window");

	bam.ctx = ctx;
	bam.running = &running;
	bam.ev = &maus_event;
	bam.grid = &test_grid;

	test_grid = grid_init(200, 200);
}

static void set_pixel(unsigned x, unsigned y, uint32_t col)
{
	if (x >= ctx->width|| y >= ctx->height) {
		bamerr = ERR_DRAW_OOB;
		return;
	}

	MAUS_PIXEL_AT(ctx, x, y) = col;
}

int main(int argc, char* argv[])
{
	if (argc > 1) {
		if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
			printf("bam version %s\n", BAM_VERSION);
			return EXIT_SUCCESS;
		}
		else {
			printf(HELP_MESSAGE);
			return EXIT_SUCCESS;
		}
	}

	setup();
	run();

	return EXIT_SUCCESS;
}

