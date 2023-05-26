/**
 * interrupt.c - Contains all interruot related configurations for our driver
*/
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <asm/io.h>
#include "42kb.h"

struct work_struct kb_wq;

// workqueue function
/**
 * read_key - Actual logic for handling keypresses
*/
void read_key(struct work_struct *unused)
{
	int scancode = inb(KB_PORT);
	// queue_data *q_data = container_of(&kb_wq, queue_data, worker);
	printk("WQ SCANCODE %x, qdata %d\n", scancode, 123);
}

irqreturn_t handler(int irq, void *dev_id){
	// printk(KERN_INFO "IRQ HANDLED !\n");

	// call workqueue here
	schedule_work(&kb_wq);

	return IRQ_HANDLED;
}

int ft_register_interrupt(void)
{
	// declare queue data
	// queue_data *q_data;
	// q_data = 0;
	// q_data = kmalloc(
	// 	sizeof(queue_data),
	// 	GFP_KERNEL
	// );
	// q_data->test = 69;
	// q_data->worker = kb_wq;

	// declare work queue action
	// INIT_WORK(&kb_wq, read_key);

	return request_irq(KB_IRQ, &handler, IRQF_SHARED, "ft_kb", g_driver);
}

void ft_deregister_interrupt(void)
{
	free_irq(KB_IRQ, g_driver);
}