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

	// free driver struct and events 
	if (driver)
	{
		if (driver->events_head)
		{
			curr = list_entry(driver->events_head->list.next, event_struct, list);
			// free refrences to other nodes ...
			while (&(curr->list) != &(driver->events_head->list))
			{
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


event_struct *ft_create_event(
	int scan_code,
	int is_pressed,
	char *name,
	int time,
	int ascii_value
	)
{
	event_struct *res;

	res = 0;
	res = kmalloc(
		sizeof(event_struct),
		GFP_KERNEL
	);
	res->scan_code = scan_code;
	res->is_pressed = is_pressed;
	res->name = name;
	res->time = time;
	res->ascii_value = ascii_value;
	INIT_LIST_HEAD(&(res->list));

	return res;
}

void ft_free_event(event_struct *event)
{
	if (event->name)
		kfree(event->name);
	kfree(event);
}

// char *ft_scancodetostr(int scancode, int isUpper)
// {

// }