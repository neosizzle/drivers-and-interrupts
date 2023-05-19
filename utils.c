#include <linux/kernel.h>
#include "42kb.h"

void ft_log(char *str)
{
	printk(KERN_INFO "[42-KB] %s", str);
}

void ft_warn(char *str)
{
	printk(KERN_WARNING "[42-KB] WARN - %s", str);
}

// char *ft_scancodetostr(int scancode, int isUpper)
// {

// }