/**
 * interrupt.c - Contains all interruot related configurations for our driver
*/
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <asm/io.h>
#include "42kb.h"

queue_data *q_data;

// workqueue function
/**
 * read_key - Actual logic for handling keypresses
*/
void read_key(struct work_struct *workqueue)
{
	int scancode = inb(KB_PORT);
	queue_data *q_data = container_of(workqueue, queue_data, worker);
	printk("WQ SCANCODE %x, qdata %d\n", scancode, q_data->test);
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
	q_data = 0;
	q_data = kmalloc(
		sizeof(queue_data),
		GFP_KERNEL
	);
	q_data->test = 69;
	// declare work queue action
	INIT_WORK(&(q_data->worker), read_key);



	return request_irq(KB_IRQ, &handler, IRQF_SHARED, "ft_kb", g_driver);
}

void ft_deregister_interrupt(void)
{
	free_irq(KB_IRQ, g_driver);
}