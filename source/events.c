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
	int cx = bam->ctx->cursor.x / bam->scale;
	int cy = bam->ctx->cursor.y / bam->scale;

	if (bam->ctx->mouse_buttons[MAUS_MOUSE_BUTTON_LEFT]) {
		if (!(cx > grid->width || cy > grid->height))
			grid_set_pixel(grid, cx, cy, !(grid_get_pixel(grid, cx, cy)));
	}

	if (bam->ev->mouse.button.button == MAUS_MOUSE_BUTTON_SCROLL_UP) {
		if (!(bam->scale+1 > 1000)) {
			bam->scale += 1;
			bam->ev->resize.width = bam->grid->width * bam->scale;
			bam->ev->resize.height = bam->grid->height * bam->scale;
			handle_resize(bam);
		}
	}

	if (bam->ev->mouse.button.button == MAUS_MOUSE_BUTTON_SCROLL_DOWN) {
		if (!(bam->scale-1 < 1)) {
			bam->scale -= 1;
			bam->ev->resize.width = bam->grid->width * bam->scale;
			bam->ev->resize.height = bam->grid->height * bam->scale;
			handle_resize(bam);
		}
	}
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
	int sx;
	int sy;
	if (rw == ow && rh == oh)
		return;

	sx = rw / bam->grid->width;
	sy = rh / bam->grid->height;

	bam->scale = sx < sy ? sx : sy;

	if (bam->scale < 1)
		bam->scale = 1;

	rw = bam->grid->width * bam->scale;
	rh = bam->grid->height * bam->scale;

	maus_resize(bam->ctx, rw, rh);
}

static void handle_redraw(Bam* bam)
{
	(void) bam;
}

