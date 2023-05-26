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

queue_data *ft_create_q_data(int is_shift, int is_caps)
{
	queue_data *q_data;

	q_data = 0;
	q_data = kmalloc(
		sizeof(queue_data),
		GFP_KERNEL
	);
	q_data->is_shift = kmalloc(
		sizeof(int),
		GFP_KERNEL
	);
	q_data->is_caps = kmalloc(
		sizeof(int),
		GFP_KERNEL
	);
	*(q_data->is_shift) = is_shift;
	*(q_data->is_caps) = is_caps;
	return q_data;
}

void ft_free_q_data(queue_data * q_data)
{
	if (q_data)
	{
		flush_work(&q_data->worker);
		if (q_data->is_shift)
			kfree(q_data->is_shift);
		if (q_data->is_caps)
			kfree(q_data->is_caps);
		kfree(q_data);
	}
}

// char *ft_scancodetostr(int scancode, int isUpper)
// {

// }