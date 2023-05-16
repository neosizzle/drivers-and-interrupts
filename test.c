#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("jng");
MODULE_LICENSE("GPL");

void print_hello(void)
{
	printk(KERN_INFO "print Hello ok !\n");
}