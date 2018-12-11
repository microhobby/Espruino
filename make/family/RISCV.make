ifeq ($(BOARD),HIFIVE1)
  # This is experimental
  $(info *********************************)
  $(info *         HIFIVE1               *)
  $(info *********************************)
  export CCPREFIX=/media/castello/Linus/labs/riscv/freedom-e-sdk/work/build/riscv-gnu-toolchain/riscv64-unknown-elf/prefix/bin/riscv64-unknown-elf-
endif

CFLAGS += -c
CFLAGS += -march=rv32imac
CFLAGS += -mabi=ilp32
CFLAGS += -mcmodel=medany -include sys/cdefs.h
LDFLAGS += -march=rv32imac -mabi=ilp32 -mcmodel=medany
LDFLAGS += -T targetlibs/fe300/env/freedom-e300-arty/flash.lds
DEFINES += -DUSE_PLIC -DUSE_M_TIME
INCLUDE += -I$(ROOT)/targets/riscv
INCLUDE += -I$(ROOT)/targetlibs/fe300/drivers
INCLUDE += -I$(ROOT)/targetlibs/fe300/include
INCLUDE += -I$(ROOT)/targetlibs/fe300/env
INCLUDE += -I$(ROOT)/targetlibs/fe300/env/freedom-e300-hifive1
SOURCES +=                              \
targets/riscv/main.c                    \
targets/riscv/jshardware.c		\
targets/riscv/uart.c			\
targetlibs/fe300/drivers/plic/plic_driver.c
