cc="x86_64-linux-gnu-gcc-13"
obj-m += nflkm_hook.o readshadow.o
all:
	make CC=$(cc) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make CC=$(cc) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

