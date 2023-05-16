#include <linux/kernel.h>
#include <linux/module.h>

void print_hello(void)
{
	printk(KERN_INFO "print Hello ok !\n");
}