/**
 * interrupt.c - Contains all interruot related configurations for our driver
*/
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <asm/io.h>
#include "42kb.h"

queue_data *q_data;

/**
 * read_key - Actual logic for handling keypresses
*/
void read_key(struct work_struct *workqueue)
{
	int scancode = inb(KB_PORT);
	int is_pressed = 1;
	ft_key key;

	// queue_data *q_data = container_of(workqueue, queue_data, worker);

	// event creation
	if (scancode >= 0x80) is_pressed = 0;
	if (!is_pressed) scancode -= 0x80;

	key = scancode_table[scancode];
	if (is_pressed)
	{
		if (key.ascii == -1)
			printk("unknown key pressed\n");
		else
			printk("%s is pressed\n", key.name);
	}
	else
	{
		if (key.ascii == -1)
			printk("unknown key released\n");
		else
			printk("%s is released\n", key.name);
	}

	// event storing

	// post processing (shift, caps) 

	// output
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

	// declare work queue action
	INIT_WORK(&(q_data->worker), read_key);



	return request_irq(KB_IRQ, &handler, IRQF_SHARED, "ft_kb", g_driver);
}

void ft_deregister_interrupt(void)
{
	ft_free_q_data(q_data);
	free_irq(KB_IRQ, g_driver);
}