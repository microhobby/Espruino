ifeq ($(BOARD),HIFIVE1)
  # This is experimental
  $(info *********************************)
  $(info *         HIFIVE1               *)
  $(info *********************************)
  export CCPREFIX=/media/castello/Linus/labs/riscv/freedom-e-sdk/work/build/riscv-gnu-toolchain/riscv64-unknown-elf/prefix/bin/riscv64-unknown-elf-
endif

CFLAGS += -fno-builtin-printf -nostartfiles
CFLAGS += -g
CFLAGS += -march=rv32imac
CFLAGS += -mabi=ilp32
CFLAGS += -mcmodel=medany
CFLAGS += -imultilib
LDFLAGS += -march=rv32imac -mabi=ilp32 -mcmodel=medany
LDFLAGS += -T targetlibs/fe300/env/freedom-e300-arty/flash.lds
DEFINES += -DHIFIVE1
INCLUDE += -I$(ROOT)/targets/riscv
INCLUDE += -I$(ROOT)/targetlibs/fe300/drivers
INCLUDE += -I$(ROOT)/targetlibs/fe300/include
INCLUDE += -I$(ROOT)/targetlibs/fe300/env
INCLUDE += -I$(ROOT)/targetlibs/fe300/env/freedom-e300-hifive1
SOURCES +=                              \
targets/riscv/uart.c			\
targets/riscv/main.c                    \
targets/riscv/jshardware.c
