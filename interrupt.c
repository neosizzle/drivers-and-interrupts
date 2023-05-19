/**
 * interrupt.c - Contains all interruot related configurations for our driver
*/
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <asm/io.h>
#include  <linux/workqueue.h>
#include "42kb.h"

struct test* event_list;

// workqueue function
void workqueue_fn(struct work_struct *)
{
	// int scancode = inb(KB_PORT);
	// printk("WQ SCANCODE %x\n", scancode);
	printk("in workeueue\n");
}

irqreturn_t handler(int irq, void *dev_id){
	// printk(KERN_INFO "IRQ HANDLED !\n");

	// call workqueue here
	// struct work_struct workqueue;
	DECLARE_WORK(workqueue, workqueue_fn);
	int schedule_res = schedule_work(&workqueue);
	// printk("workqueue res %d\n", schedule_res);

	int scancode = inb(KB_PORT);
	printk("SCANCODE %x\n", scancode);
	return IRQ_HANDLED;
}

int ft_register_interrupt(struct test* _event_list)
{
	struct irq_desc *desc;
	event_list = _event_list;
	return request_irq(KB_IRQ, &handler, IRQF_SHARED, "ft_kb", event_list);
}

void ft_deregister_interrupt(void)
{
	free_irq(KB_IRQ, event_list);
}