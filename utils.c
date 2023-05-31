#include <linux/kernel.h>
#include "42kb.h"

/**
 * ft_log - log to kernel console
*/
void ft_log(char *str)
{
	printk(KERN_INFO "[42-KB] %s", str);
}

/**
 * ft_warn - warn to kernel console
*/
void ft_warn(char *str)
{
	printk(KERN_WARNING "[42-KB] WARN - %s", str);
}

/**
 * ft_free_driver - free driver struct
*/
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

/**
 * ft_create_driver - make driver struct
*/
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

/**
 * ft_create_event - make keystroke event struct
*/
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

/**
 * ft_free_event - free keystroke event struct
*/
void ft_free_event(event_struct *event)
{
	if (event->name)
		kfree(event->name);
	kfree(event);
}

/**
 * ft_create_q_data - make queue data struct
*/
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

/**
 * ft_free_q_data - free queue data struct
*/
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

/**
 * generate_event - generate event object given scancode and queuedata
*/
event_struct *ft_generate_event(queue_data q_data, int scancode)
{
	event_struct *res;
	int is_pressed = 1;
	int is_upper = -1;
	ft_key key;

	res = kmalloc(sizeof(event_struct), GFP_KERNEL);
	if (!res) return res;
	if (scancode >= 0x80) is_pressed = 0;
	if (!is_pressed) scancode -= 0x80;

	printk("q_data.is_shift %d, q_data.is_caps %d, is_upper %d\n", *(q_data.is_shift), *(q_data.is_caps), is_upper);
	if (*(q_data.is_shift)) is_upper *= -1;
	if (*(q_data.is_caps)) is_upper *= -1;
	printk("2 q_data.is_shift %d, q_data.is_caps %d, is_upper %d\n", *(q_data.is_shift), *(q_data.is_caps), is_upper);

	key = scancode_table[scancode];
	res->scan_code = scancode;
	res->is_pressed = is_pressed;
	res->name = key.name ? (is_upper > 0? key.caps_name : key.name) : "unknown";
	res->time = 69;
	res->ascii_value = is_upper ? key.caps_ascii : key.ascii;
	
	// init list head
	INIT_LIST_HEAD(&(res->list));

	return res;
}

// char *ft_scancodetostr(int scancode, int isUpper)
// {

// }