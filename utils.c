#include <linux/kernel.h>
#include "42kb.h"

void ft_log(char *str)
{
	printk(KERN_INFO "[42KB] %s", str);
}

void ft_warn(char *str)
{
	printk(KERN_WARNING "[42KB] WARN - %s", str);
}