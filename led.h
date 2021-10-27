#ifndef _LED_H_
#define _LED_H_
#define __ASSEMBLY__
#include <mach/regs-gpio.h>
#include <mach/map.h>

/* GPB config register virtul addr */
#define S3C2440_GPBCON S3C2410_GPBCON

/* GPB data register virtul addr*/
#define S3C2440_GPBDAT S3C2410_GPBDAT

#define S3C2440_GPB5 _LED1
#define S3C2440_GPB6 _LED2
#define S3C2440_GPB7 _LED3
#define S3C2440_GPB8 _LED4

#define _LED1 0
#define _LED2 1
#define _LED3 2
#define _LED4 3

/* Config cmd */
#define S3C2440_GPIO_INPUT   00 
#define S3C2440_GPIO_OUTPUT  01

/* Data cmd */
#define LED_ON 0
#define LED_OFF 1

/* Config GPIO pin */
#define S3C2440_GPB5_CFG(cmd)  (cmd << 10)
#define S3C2440_GPB6_CFG(cmd)  (cmd << 12)
#define S3C2440_GPB7_CFG(cmd)  (cmd << 14)
#define S3C2440_GPB8_CFG(cmd)  (cmd << 16)

/* Set GPIO data */
#define S3C2440_GPB5_DATA(cmd)  (cmd << 5)
#define S3C2440_GPB6_DATA(cmd)  (cmd << 6)
#define S3C2440_GPB7_DATA(cmd)  (cmd << 7)
#define S3C2440_GPB8_DATA(cmd)  (cmd << 8)

void set_led(unsigned long val);
void config_led(unsigned long val);


#endif	/* _LED_H_ */
