#include <stdbool.h>

#include "iob_seg_swreg.h"

//SEG functions

//Set SEG base address
void seg_init(int base_address);


//Set values on outputs
void seg_set(int outputs);

void seg_data_cat(uint32_t  value_cat);

void seg_data_ano(uint32_t  value_ano);


