#include <linux/errno.h>
#include "led.h"


int s3c2440_gpio_setpin(unsigned long pin, unsigned long cmd)
{
	
	switch (pin)
	{
		case _LED1:
			set_led(S3C2440_GPB5_DATA(cmd));
			break;
		case _LED2:
			set_led(S3C2440_GPB6_DATA(cmd));
			break;
		case _LED3:
			set_led(S3C2440_GPB7_DATA(cmd));
			break;
		case _LED4:
			set_led(S3C2440_GPB8_DATA(cmd));
			break;
		default:
			return -EINVAL;

	}
	return 0;
}

int s3c2440_gpio_cfgpin(unsigned long pin, unsigned long cmd)
{
	
	switch (pin)
	{
		case _LED1:
			config_led(S3C2440_GPB5_CFG(cmd));
			break;
		case _LED2:
			config_led(S3C2440_GPB6_CFG(cmd));
			break;
		case _LED3:
			config_led(S3C2440_GPB7_CFG(cmd));
			break;
		case _LED4:
			config_led(S3C2440_GPB8_CFG(cmd));
			break;
		default:
			return -EINVAL;

	}
	return 0;
}


void set_led(unsigned long val)
{
	__asm__ __volatile__(
		"str %[val], [%[ioaddr]] \n\t"
		::[val] "r"(val), [ioaddr] "r"(S3C2440_GPBDAT): "memory"	
	);
	return;
}

void config_led(unsigned long val)
{
	__asm__ __volatile__(
		"str %[val], [%[ioaddr]] \n\t"
		::[val] "r"(val), [ioaddr] "r"(S3C2440_GPBCON): "memory"	
	);
	return;
}