ifeq ($(filter SEG, $(HW_MODULES)),)

include $(SEG_DIR)/config.mk

#add itself to HW_MODULES list
HW_MODULES+=SEG

SEG_INC_DIR:=$(SEG_HW_DIR)/include
SEG_SRC_DIR:=$(SEG_HW_DIR)/src


#include files
VHDR+=$(wildcard $(SEG_INC_DIR)/*.vh)
VHDR+=iob_seg_swreg_gen.vh iob_seg_swreg_def.vh
VHDR+=$(LIB_DIR)/hardware/include/iob_lib.vh $(LIB_DIR)/hardware/include/iob_s_if.vh $(LIB_DIR)/hardware/include/iob_gen_if.vh

#hardware include dirs
INCLUDE+=$(incdir). $(incdir)$(SEG_INC_DIR) $(incdir)$(LIB_DIR)/hardware/include

#sources
VSRC+=$(wildcard $(SEG_SRC_DIR)/*.v)

seg-hw-clean:
	@rm -rf $(SEG_HW_DIR)/fpga/vivado/XCKU $(SEG_HW_DIR)/fpga/quartus/CYCLONEV-GT

.PHONY: seg-hw-clean

endif
