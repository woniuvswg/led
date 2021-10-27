#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "memdev.h"

int main(int argc, char *argv[])
{
	int on;
	int fd;

	if (argc != 2 || sscanf(argv[1], "%d", &on) != 1 || on < 0 || on > 1)
	{
		fprintf(stderr, "Usage:%s 0|1", argv[0]);
		exit(1);
	}

	fd = open("/dev/my-leds", 0);
	if (fd < 0)
	{
		perror("open device my-leds error");
		exit(1);
	}

	/* 通过ioctl来控制灯的亮灭 */
	if (on)
	{
		ioctl(fd, MEMDEV_IOC_ON, 0);
		printf("turn on all leds!\n");
	}
	else
	{
		ioctl(fd, MEMDEV_IOC_OFF, 0);
		printf("turn off all leds!\n");
	}

	close(fd);
	return 0;
}
