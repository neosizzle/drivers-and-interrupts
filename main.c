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
drv_struct *g_driver; // declaration of global struct
// struct ft_key scancode_table[MAX_SCANCODE_SIZE] = { // declaration of scancode table
// 	// fill array with default value
// 	[0x0 ... MAX_SCANCODE_SIZE - 1] = {NULL, NULL, -1, -1},

// 	// fill known values
// 	[0x10] = {"q", "Q", 'q', 'Q'},
// 	[0x11] = {"w", "W", 'w', 'W'},
// 	[0x12] = {"e", "E", 'e', 'E'},
// 	[0x13] = {"r", "R", 'r', 'R'},
// 	[0x14] = {"t", "T", 't', 'T'},
// 	[0x15] = {"y", "Y", 'y', 'Y'},
// 	[0x16] = {"u", "U", 'u', 'U'},
// 	[0x17] = {"i", "I", 'i', 'I'},
// 	[0x18] = {"o", "O", 'o', 'O'},
// }

/**
 * Module Init. Registers a USB device and creates a misc device in /dev/ft_module_keyboard
*/
int init_module(void)
{
	int result ;
	event_struct* first_event;

	// create driver struct
	g_driver = ft_create_driver();
	if (!g_driver)
	{
		ft_warn("Allocation for driver struct failed");
		return 1;
	}

	// create head event
	first_event = ft_create_event(-1, -1, NULL, -1, -1);
	if (!first_event)
	{
		ft_warn("Allocation for first event failed");
		return 1;
	}
	g_driver->events_head = first_event;

	result = ft_register_usb();
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
	ft_free_driver(g_driver);
	
}
