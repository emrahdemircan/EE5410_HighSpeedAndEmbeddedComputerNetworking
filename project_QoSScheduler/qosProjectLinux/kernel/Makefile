obj-m += module_5410.o
module_5410-objs := outputQueueModule.o ethernetReceiver.o ethernetScheduler.o ethernetSender.o netlink.o stats.o
KDIR := /lib/modules/$(shell uname -r)/build
EXTRA_CFLAGS += -I$(PWD)
EXTRA_CFLAGS += -I$(PWD)/external
EXTRA_CFLAGS += -O
PWD := $(shell pwd)
all:
	make -C ${KDIR} M=${PWD} modules
	rm -f *.o .*.cmd modules.order Module.symvers *.mod.c
	rm -Rf .tmp_versions/*
	rmdir .tmp_versions
.PHONY: clean
clean:
	make -C ${KDIR} M=${PWD} clean
