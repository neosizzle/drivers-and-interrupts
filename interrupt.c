/**
 * interrupt.c - Contains all interruot related configurations for our driver
*/
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <asm/io.h>
#include <linux/input.h>
#include "42kb.h"

#include <linux/tty.h>

queue_data *q_data;

// /dev/input/by-path to find 
// https://github.com/haloboy777/keyboard-driver/blob/master/driver.c
void my_printk(char *string)
{
	struct tty_struct *my_tty;
	my_tty=get_current_tty();
	
	

	if(my_tty!=NULL)
	{
		(*my_tty->ops->write)(my_tty, string, strlen(string));
		(*my_tty->ops->write)(my_tty, "\015\012", 2);
	}
	else 
		printk("TTY IS NULL\n");
}


/**
 * read_key - Actual logic for handling keypresses
*/
void read_key(struct work_struct *workqueue)
{
	int scancode = inb(KB_PORT);
	int is_pressed = 1;
	ft_key key;

	queue_data *q_data = container_of(workqueue, queue_data, worker);

	// event creation
	event_struct *event = ft_generate_event(*q_data, scancode);
	// if (event->is_pressed){
	// 	printk("%s is pressed\n", event->name);
	// }
	// else{
	// 	printk("%s is released\n", event->name);
	// }

	// test haha
	my_printk("hello\n");

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