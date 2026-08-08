#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <maus.h>

#include "common.h"

static void run(void);
static void setup(void);

Bam bam = { 0 };
static Maus* ctx = NULL;
static MausEvent maus_event;
static int running = 0;

static MausColor col_white = { 255, 255, 255, 255 };

static void run(void)
{
	running = 1;
	while (running) {
		maus_event_wait(ctx, &maus_event);
		maus_clear(ctx, col_white);

		maus_present(ctx);
	}
}

static void setup(void)
{
	ctx = maus_init("ximus", 100, 100, 10, 10);
	if (!ctx)
		maus_die("Failed to initialise maus context");

	if (!maus_create_window(ctx))
		maus_die("Failed to create maus window");

	bam.ctx = ctx;
	bam.running = &running;
	bam.ev = &maus_event;
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

