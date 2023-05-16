obj-m += 42kb.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/srcs modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/srcs clean
