/*  
 * main.c - The entry point to the module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/hid.h>
#include <linux/irqnr.h>
#include "42kb.h"

MODULE_AUTHOR("jng");
MODULE_LICENSE("GPL");

/**
 * Module Init. Registers a USB device and creates a misc device in /dev/ft_module_keyboard
*/
int init_module(void)
{
	// todo heap this
	// struct test keylogger = {
	// 	.gay = 1,
	// 	.list = NULL
	// };
	// LIST_HEAD(&keylogger);

	int result = ft_register_usb();
	if (result)
		ft_warn("USB Registration failed");
	else
		ft_log("USB Registration OK");

	result = ft_create_misc_device();
	if (result)
		ft_warn("MiscDev Registration failed");
	else
		ft_log("MiscDev Registration OK");

	result = ft_register_interrupt();
	if (result)
		ft_warn("IRQ Registration failed");
	else
		ft_log("IRQ Registration OK");

	ft_log("Module initialized");
	return 0;
}

void cleanup_module(void)
{
	ft_log("Cleaning up module");
	ft_deregister_interrupt();
	ft_destroy_misc_device();
	ft_deregister_usb();	
}
