#ifndef COMMON_H
#define COMMON_H

#include <maus.h>

#ifndef BAM_VERSION
	#define BAM_VERSION "..who knows"
#endif /* BAM_VERSION */

#define HELP_MESSAGE \
"bam:\n" \
"\t[-v|--version] : Show the program version\n"
#define KEY(k) (ctx->key_syms[MAUS_KEY_##k])

typedef enum {
	ERR_OK,

	ERR_GRID_ALLOC,
	ERR_GRID_INVALID,
	ERR_GRID_ACCESS_OOB,

	ERR_DRAW_OOB,

	ERR_LAST
} ErrorType;

typedef struct {
	Maus*      ctx;
	MausEvent* ev;

	int* running;
} Bam;

void bam_log_err(ErrorType err);

extern ErrorType bamerr;

#endif /* COMMON_H */

