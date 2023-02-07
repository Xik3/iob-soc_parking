include $(SEG_DIR)/config.mk

SEG_SW_DIR:=$(SEG_DIR)/software

#include
INCLUDE+=-I$(SEG_SW_DIR)

#headers
HDR+=$(SEG_SW_DIR)/*.h iob_seg_swreg.h

#sources
SRC+=$(SEG_SW_DIR)/iob-seg.c

iob_seg_swreg.h: $(SEG_DIR)/mkregs.conf
	$(MKREGS) iob_seg $(SEG_DIR) SW
