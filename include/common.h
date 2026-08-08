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

typedef struct {
	Maus*      ctx;
	MausEvent* ev;

	int* running;
} Bam;

#endif /* COMMON_H */

