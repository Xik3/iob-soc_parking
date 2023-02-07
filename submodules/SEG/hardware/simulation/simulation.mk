include $(SEG_DIR)/hardware/hardware.mk

DEFINE+=$(defmacro)VCD

VSRC+=$(wildcard $(SEG_HW_DIR)/testbench/*.v)
