#ifndef EVENTS_H
#define EVENTS_H

#include <maus.h>

#include "common.h"

/* see maus_input.h for all
   possible key values */
#define KCLOSE (KEY(Q) && KEY(CONTROL_L))

#define BDRAW  (BTN(LEFT))
#define BERASE (BTN(RIGHT))

extern void (*event_handler[MAUS_EV_LAST])(Bam*);

#endif /* EVENTS_H */

