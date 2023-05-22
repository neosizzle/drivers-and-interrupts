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

void ft_free_driver(drv_struct *driver)
{
	event_struct *curr;
	event_struct *temp;

	int	cnt = 0;

	// free driver struct and events 
	if (driver)
	{
		if (driver->events_head)
		{
			curr = list_entry(curr->list.next, event_struct, list);
			// free refrences to other nodes ...
			while (&(curr->list) != driver->events_head.list)
			{
				printk("free_driver %d\n..", ++cnt);
				// temp is curr->list.next
				temp = list_entry(curr->list.next, event_struct, list);

				// free curr
				kfree(curr);

				// curr is temp.next
				curr = temp;
			}
			
			// free self
			kfree(curr);
		}
		kfree(driver);
	}	
}

drv_struct *ft_create_driver(void)
{
	drv_struct *res;

	res = 0;
	res = kmalloc(
		sizeof(drv_struct),
		GFP_KERNEL
	);
	return res;
}

// char *ft_scancodetostr(int scancode, int isUpper)
// {

// }