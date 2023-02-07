SHELL:=/bin/bash

TOP_MODULE=iob_seg

#PATHS
REMOTE_ROOT_DIR ?=sandbox/iob-seg
SIM_DIR ?=$(SEG_HW_DIR)/simulation/$(SIMULATOR)
SEG_DIR ?=$(SEG_DIR)/hardware/fpga/$(FPGA_COMP)
DOC_DIR ?=

LIB_DIR ?=$(SEG_DIR)/submodules/LIB
SEG_HW_DIR:=$(SEG_DIR)/hardware

#MAKE SW ACCESSIBLE REGISTER
MKREGS:=$(shell find $(LIB_DIR) -name mkregs.py)

#DEFAULT FPGA FAMILY AND FAMILY LIST
FPGA_FAMILY ?=XCKU
FPGA_FAMILY_LIST ?=CYCLONEV-GT XCKU

#DEFAULT DOC AND DOC LIST
DOC ?=pb
DOC_LIST ?=pb ug

# default target
default: sim

# VERSION
VERSION ?=V0.1
$(TOP_MODULE)_version.txt:
	echo $(VERSION) > version.txt

#cpu accessible registers
iob_seg_swreg_def.vh iob_seg_swreg_gen.vh: $(SEG_DIR)/mkregs.conf
	$(MKREGS) iob_seg $(SEG_DIR) HW

seg-gen-clean:
	@rm -rf *# *~ version.txt

.PHONY: default seg-gen-clean
