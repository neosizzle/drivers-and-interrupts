obj-m += 42kb.o
42kb-y := test.o main.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
