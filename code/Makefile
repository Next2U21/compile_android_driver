obj-m := mydriver.o

PWD := $(shell pwd)
KDIR := $(shell pwd)/common

all:
    $(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
    $(MAKE) -C $(KDIR) M=$(PWD) clean