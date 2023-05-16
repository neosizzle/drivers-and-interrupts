#include <linux/kernel.h>
#include "42kb.h"

void ft_log(char *str)
{
	printk(KERN_INFO YEL "[42KB] %s" RESET, str);
}

void ft_warn(char *str)
{
	printk(KERN_WARNING YEL "[42KB] WARN - %s" RESET, str);
}