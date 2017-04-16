obj-m += ioctl_module.o
KERNEL_VERSION ?= $(shell uname -r)
KDIR ?= /lib/modules/$(KERNEL_VERSION)/build

ioctl-tester-obj = ioctl_tester

ioctl_tester: CFLAGS += -static -std=c99 -Wall -g

all: module ioctl_tester

module:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

ioctl_tester: $(ioctl-tester-obj)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf $(ioctl-tester-obj)
