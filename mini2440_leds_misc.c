#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>
#include <asm/io.h>
#include <asm/system.h>

#include "memdev.h"
#include "led.h"
#define DEVICE_NAME "my-leds"

static unsigned long led_table[] = 
{
	S3C2440_GPB5,
	S3C2440_GPB6,
	S3C2440_GPB7,
	S3C2440_GPB8,
};


static int s3c2440_leds_ioctl(struct inode *inode, struct file *filep, unsigned int cmd, unsigned long arg)
{
	int i = 0;
	/* 检测命令有效性 */
	if (_IOC_TYPE(cmd) != MEMDEV_IOC_MAGIC)
	{
		return -EINVAL;
	}
	if (_IOC_NR(cmd) > MEMDEV_IOC_MAXNR)
	{
		return -EINVAL;
	}

	/* 根据命令，执行相应操作 */
	switch (cmd)
	{
		case MEMDEV_IOC_OFF:
			/* 灯全灭 */
			for(i = 0; i < 4; i++)
			{
				s3c2440_gpio_setpin(led_table[i], LED_OFF);
				printk(DEVICE_NAME "@led_%d is off\n", i);
			}
			return 0;
		case MEMDEV_IOC_ON:
			/* 灯全亮 */
			for(i = 0; i < 4; i++)
			{
				s3c2440_gpio_setpin(led_table[i], LED_ON);
				printk(DEVICE_NAME "@led_%d is on\n", i);
			}
			return 0;
		default:
			return -EINVAL;
	}
	
}

/* 文件操作结构体 */
static struct file_operations dev_fops = 
{
	.owner = THIS_MODULE,
	.ioctl = s3c2440_leds_ioctl,
};

/* 混杂设备结构体 */
static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};

static int __init dev_init(void)
{
	int ret = 0;
	int i;
	printk(DEVICE_NAME"Modlue init\n");
	/* 配置GPIO寄存器, 把4个GPIO 设置位输出，默认灯全灭 */
	for (i = 0; i < 4; i++)
	{
		s3c2440_gpio_cfgpin(led_table[i], S3C2440_GPIO_OUTPUT);
		s3c2440_gpio_setpin(led_table[i], LED_OFF);
		printk("%X   %X\n", S3C2440_GPBDAT, S3C2440_GPBCON);
	}

	/* 注册混杂型设备驱动 */
	ret = misc_register(&misc);

	printk(DEVICE_NAME"\tinitialized\n");

	return ret;
}

static void __exit dev_exit(void)
{
	/* 注销混杂型字符设备驱动 */
	misc_deregister(&misc);
}

module_init(dev_init);
module_exit(dev_exit);

MODULE_AUTHOR("Josef Luo");
MODULE_LICENSE("GPL'");

