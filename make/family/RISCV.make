ifeq ($(BOARD),HIFIVE1)
  # This is experimental
  $(info *********************************)
  $(info *         HIFIVE1               *)
  $(info *********************************)
  export CCPREFIX=/media/castello/Linus/labs/riscv/freedom-e-sdk/work/build/riscv-gnu-toolchain/riscv64-unknown-elf/prefix/bin/riscv64-unknown-elf-
endif

CFLAGS += -fno-builtin-printf
CFLAGS += -march=rv32imac
CFLAGS += -mabi=ilp32
CFLAGS += -mcmodel=medany
LDFLAGS += -march=rv32imac -mabi=ilp32 -mcmodel=medany
LDFLAGS += -T targetlibs/fe300/env/freedom-e300-hifive1/flash.lds -nostartfiles
LDFLAGS += -Ltargetlibs/fe300/env --specs=nano.specs
DEFINES += -DUSE_PLIC -DUSE_M_TIME
INCLUDE += -I$(ROOT)/targets/riscv
INCLUDE += -I$(ROOT)/targetlibs/fe300/drivers
INCLUDE += -I$(ROOT)/targetlibs/fe300/include
INCLUDE += -I$(ROOT)/targetlibs/fe300/env
INCLUDE += -I$(ROOT)/targetlibs/fe300/env/freedom-e300-hifive1

ASMSOURCES += 				\
targetlibs/fe300/env/start.S \
targetlibs/fe300/env/entry.S

SOURCES +=                              \
targetlibs/fe300/drivers/plic/plic_driver.c \
targetlibs/fe300/env/freedom-e300-hifive1/init.c \
targetlibs/fe300/libwrap/stdlib/malloc.c \
targetlibs/fe300/libwrap/sys/open.c	\
targetlibs/fe300/libwrap/sys/lseek.c	\
targetlibs/fe300/libwrap/sys/read.c	\
targetlibs/fe300/libwrap/sys/write.c	\
targetlibs/fe300/libwrap/sys/fstat.c	\
targetlibs/fe300/libwrap/sys/stat.c	\
targetlibs/fe300/libwrap/sys/close.c	\
targetlibs/fe300/libwrap/sys/link.c	\
targetlibs/fe300/libwrap/sys/unlink.c	\
targetlibs/fe300/libwrap/sys/execve.c	\
targetlibs/fe300/libwrap/sys/fork.c	\
targetlibs/fe300/libwrap/sys/getpid.c	\
targetlibs/fe300/libwrap/sys/kill.c	\
targetlibs/fe300/libwrap/sys/wait.c	\
targetlibs/fe300/libwrap/sys/isatty.c	\
targetlibs/fe300/libwrap/sys/times.c	\
targetlibs/fe300/libwrap/sys/sbrk.c	\
targetlibs/fe300/libwrap/sys/_exit.c	\
targetlibs/fe300/libwrap/sys/puts.c	\
targetlibs/fe300/libwrap/misc/write_hex.c	\
targets/riscv/irq.c			\
targets/riscv/uart.c			\
targets/riscv/main.c                    \
targets/riscv/jshardware.c
