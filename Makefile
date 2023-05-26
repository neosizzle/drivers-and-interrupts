obj-m += 42kb.o
42kb-y := main.o usb.o utils.o device.o interrupt.o tmpfile.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
