#ifndef _MEMDEV_H_
#define _MEMDEV_H_

#include <linux/ioctl.h>

/* 定义幻数 */
#define MEMDEV_IOC_MAGIC 'k'

/* 定义命令 */
#define MEMDEV_IOC_ON _IO(MEMDEV_IOC_MAGIC, 1)
#define MEMDEV_IOC_OFF _IO(MEMDEV_IOC_MAGIC, 2)

#define MEMDEV_IOC_MAXNR 2

extern int s3c2440_gpio_setpin(unsigned long pin, unsigned int cmd);
extern int s3c2440_gpio_cfgpin(unsigned long pin, unsigned int cmd);


#endif	/* _MEMDEV_H_ */
