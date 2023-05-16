#include <linux/kernel.h>
#include <linux/module.h>

void print_hello()
{
	printk(KERN_INFO "print Hello ok !\n");
}