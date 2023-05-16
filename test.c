#include <linux/kernel.h>

void print_hello(void)
{
	printk(KERN_INFO "print Hello ok !\n");
}