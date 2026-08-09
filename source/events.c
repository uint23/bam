#include "events.h"
#include "grid.h"

static void handle_none(Bam* bam);
static void handle_close(Bam* bam);
static void handle_key(Bam* bam);
static void handle_mouse_button(Bam* bam);
static void handle_mouse_motion(Bam* bam);
static void handle_resize(Bam* bam);
static void handle_redraw(Bam* bam);

void (*event_handler[MAUS_EV_LAST])(Bam*) = {
	handle_none,
	handle_close,
	handle_key,
	handle_mouse_button,
	handle_mouse_motion,
	handle_resize,
	handle_redraw,
};

static void handle_none(Bam* bam)
{
	(void) bam;
}

static void handle_close(Bam* bam)
{
	*bam->running = 0;
}

static void handle_key(Bam* bam)
{
	Maus* ctx = bam->ctx;

	/* quit */
	if (KCLOSE)
		handle_close(bam);
}

static void handle_mouse_button(Bam* bam)
{
	Grid* grid = bam->grid;
	int cx = bam->ctx->cursor.x;
	int cy = bam->ctx->cursor.y;

	if (!bam->ctx->mouse_buttons[MAUS_MOUSE_BUTTON_LEFT])
		return;

	if (cx > grid->width || cy > grid->height)
		return;

	grid_set_pixel(grid, cx, cy, 1);
}

static void handle_mouse_motion(Bam* bam)
{
	if (bam->ctx->mouse_buttons[MAUS_MOUSE_BUTTON_LEFT])
		handle_mouse_button(bam);
}

static void handle_resize(Bam* bam)
{
	int rw = bam->ev->resize.width;
	int rh = bam->ev->resize.height;
	int ow = bam->ctx->width;
	int oh = bam->ctx->height;
	if (rw == ow && rh == oh)
		return;

	maus_resize(bam->ctx, rw, rh);
}

static void handle_redraw(Bam* bam)
{
	(void) bam;
}

