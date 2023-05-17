/**
 * interrupt.c - Contains all interruot related configurations for our driver
*/
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <asm/io.h>
#include "42kb.h"

struct test* event_list;

irqreturn_t handler(int irq, void *dev_id){
	// printk(KERN_INFO "IRQ HANDLED !\n");
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