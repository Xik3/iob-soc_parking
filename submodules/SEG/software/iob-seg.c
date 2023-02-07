#include "iob-seg.h"

//7SEG functions

//Set SEG base address
void seg_init(int base_address){
  IOB_SEG_INIT_BASEADDR(base_address);
}

//Set values on outputs
void seg_set(int value){
  IOB_SEG_SET_OUTPUT(value);
}
  
void seg_data_cat(uint32_t  value_cat){
  IOB_SEG_SET_DATA_CAT(value_cat);
}

void seg_data_ano(uint32_t  value_ano){
  IOB_SEG_SET_DATA_ANO(value_ano);
}
 
