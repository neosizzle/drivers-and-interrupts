/**
 * interrupt.c - Contains all interruot related configurations for our driver
*/
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <asm/io.h>
#include  <linux/workqueue.h>
#include "42kb.h"

struct work_struct short_wq;

// workqueue function
void short_do_tasklet(struct work_struct *unused)
{
	int scancode = inb(KB_PORT);
	printk("WQ SCANCODE %x\n", scancode);
}

irqreturn_t handler(int irq, void *dev_id){
	// printk(KERN_INFO "IRQ HANDLED !\n");

	// call workqueue here
	schedule_work(&short_wq);

	return IRQ_HANDLED;
}

int ft_register_interrupt(void)
{
	struct irq_desc *desc;

	// struct work_struct short_wq;
	// DECLARE_WORK(short_wq, short_do_tasklet);
	INIT_WORK(&short_wq, short_do_tasklet);

	return request_irq(KB_IRQ, &handler, IRQF_SHARED, "ft_kb", event_list);
}

void ft_deregister_interrupt(void)
{
	free_irq(KB_IRQ, event_list);
}