/* PC Emulation of SEG peripheral */

#include <stdint.h>
#include <stdio.h>

#include "iob_seg_swreg.h"

static uint32_t base;

void SEG_INIT_BASEADDR(uint32_t addr) {
    base = addr;
    return;
}


//Set values on outputs
void seg_set(uint32_t outputs){
}
