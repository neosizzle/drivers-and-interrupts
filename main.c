/*  
 * main.c - The entry point to the module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/hid.h>
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include "42kb.h"

MODULE_AUTHOR("jng");
MODULE_LICENSE("GPL");


irqreturn_t handler(int irq, void *dev_id){
	printk(KERN_INFO "IRQ HANDLED !\n");
	return IRQ_HANDLED;
}

// function to handle probe
int handle_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	return 0;
}

// function to handle disconnect
void handle_disconnect(struct usb_interface *intf)
{
	printk(KERN_INFO "Usb DCED !\n");
}

int init_module(void)
{
	int result = ft_register_usb();
	if (result)
		ft_warn("USB Registration failed");
	else
		ft_log("USB Registration OK");
	// request interrupt line here and pray it works

	// if interrupt here wrong or irq, gotta ditch the usb and go PURE PS2
	// int kb_irq = 1;
	// struct irq_desc *desc;

	// struct test { 
	// 	int gay;
	// };
	// struct test keylogger = {
	// 	.gay = 1,
	// };

	// int req_irq_result = request_irq(kb_irq, &handler, IRQF_SHARED, "my_keyboard", &keylogger);
	// if (req_irq_result < 0)
	// 	printk(KERN_INFO "IRQ REQUEST ERR !: %d\n", req_irq_result);
	// else
	// 	printk(KERN_INFO "IRQ REQUEST OK !\n");

	ft_log("Module initialized");
	return 0;
}

void cleanup_module(void)
{
	ft_log("Cleaning up module");
	ft_deregister_usb();
}
