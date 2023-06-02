/**
 * interrupt.c - Contains all interruot related configurations for our driver
*/
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <asm/io.h>
#include <linux/input.h>
#include "42kb.h"

queue_data *q_data;
int is_caps = 0;
int is_shift = 0;

/**
 * read_key - Actual logic for handling keypresses
*/
void read_key(struct work_struct *workqueue)
{
	int scancode = inb(KB_PORT);
	int is_pressed = 1;
	ft_key key;
	char *output_str;

	queue_data *q_data = container_of(workqueue, queue_data, worker);

	// preprocessing LOCK HERE
	q_data->is_caps = &is_caps;
	q_data->is_shift = &is_shift; 

	// event creation
	event_struct *event = ft_generate_event(*q_data, scancode);

	// event storing
	list_add_tail(&(event->list), &(q_data->driver.events_head->list));


	// post processing (shift, caps) LOCK HERE
	// if event name is caps, toggle caps
	if (!strcmp("caps", event->name) && event->is_released)
		is_caps = !is_caps;
	if (!strcmp("shift", event->name))
	{
		if (event->is_pressed)
			is_shift = 1;
		else
			is_shift = 0;
	}

	// output
	output_str = kmalloc(69420, GFP_KERNEL);
	if (event->is_pressed){
		sprintf(output_str, "%s is pressed\n", event->name);
		// printk("%s is pressed\n", event->name);
	}
	else{
		sprintf(output_str, "%s is released\n", event->name);
		// printk("%s is released\n", event->name);
	}
	ft_write_tmpfile(output_str);
	kfree(output_str);
	// printk("WQ SCANCODE %x\n", scancode);
}

irqreturn_t handler(int irq, void *dev_id){
	// printk(KERN_INFO "IRQ HANDLED !\n");
	// call workqueue here

	schedule_work(&(q_data->worker));

	return IRQ_HANDLED;
}

int ft_register_interrupt(void)
{
	// declare queue data
	q_data = ft_create_q_data(0, 0);
	if (!q_data)
	{
		ft_warn("Queue data creation failed\n");
		return 1;
	}
	q_data->driver = *(g_driver);
	// declare work queue action
	INIT_WORK(&(q_data->worker), read_key);

	return request_irq(KB_IRQ, &handler, IRQF_SHARED, "ft_kb", g_driver);
}

void ft_deregister_interrupt(void)
{
	ft_free_q_data(q_data);
	free_irq(KB_IRQ, g_driver);
}