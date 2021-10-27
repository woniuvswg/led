ifneq ($(KERNELRELEASE),)

obj-m := mini2440_leds.o
mini2440_leds-objs := mini2440_leds_misc.o led.o

else

KDIR := /opt/FriendlyARM/mini2440/linux-2.6.32.2
all: app-led
	make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-

app-led: app-led.c
	arm-linux-gcc -o $@ $^

clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers  modul*

endif