ifeq ($(filter SEG, $(SW_MODULES)),)

SW_MODULES+=SEG

include $(SEG_DIR)/software/software.mk

# add embeded sources
SRC+=iob_seg_swreg_emb.c

iob_seg_swreg_emb.c: iob_seg_swreg.h

endif
