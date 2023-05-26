/**
 * tmpfile.c - /tmp/42module_keyboard file configration
*/
#include "42kb.h"
#include <linux/fs.h>

int ft_create_tmpfile(void)
{
	struct file* infile = filp_open("/tmp/lol", O_RDONLY | O_CREAT, S_IRWXU);
	if (infile) {
		printk("opened file\n");
		filp_close(infile, NULL);
	}
	else
		printk("cannot open file\n");
	return 0;
}

void ft_destroy_tmpfile(void)
{
	
}