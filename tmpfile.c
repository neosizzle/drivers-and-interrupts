/**
 * tmpfile.c - /tmp/42module_keyboard file configration
*/
#include "42kb.h"
#include <linux/syscalls.h>

int ft_create_tmpfile(void)
{
	fd = sys_open("/tmp/lol", O_RDONLY | O_CREAT, 0);
	if (fd >= 0) {
		printk("opened file\n");
		sys_close(fd);
	}
	else
		printk("cannot open file\n");
	return 0;
}

void ft_destroy_tmpfile(void)
{
	
}