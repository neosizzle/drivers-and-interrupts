/*  
 * hello-1.c - The simplest kernel module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/usb.h>		/* Needed for driver macros*/
#include <linux/usb/input.h>
#include <linux/hid.h>
#include <linux/interrupt.h>

MODULE_AUTHOR("jng");
MODULE_LICENSE("GPL");

/*  
 * mouse_table - hardware definitions for mouse and keyboard
 */
static struct usb_device_id definition_table[] = {
	{USB_INTERFACE_INFO(
		USB_INTERFACE_CLASS_HID,
		USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_MOUSE
	)},
	{USB_INTERFACE_INFO(
		USB_INTERFACE_CLASS_HID,
		USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_KEYBOARD
	)},
	{0}
};
MODULE_DEVICE_TABLE(usb, definition_table);

irq_return_t handler(int irq, void *dev_id, struct pt_regs *regs){
	printk(KERN_INFO "IRQ HANDLED !\n");
	return IRQ_HANDLED;
}

// function to handle probe
int handle_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	// request interrupt line here and pray it works

	// if interrupt here wrong or irq, gotta ditch the usb and go PURE PS2
	int kb_irq = 0;
	int req_irq_result = request_irq(kb_irq, handler, 0, "my_keyboard", NULL);
	if (req_irq_result < 0)
		printk(KERN_INFO "IRQ REQUEST ERR !\n");
	else
		printk(KERN_INFO "IRQ REQUEST OK !\n");
	return 0;
}

// function to handle disconnect
void handle_disconnect(struct usb_interface *intf)
{
	printk(KERN_INFO "Usb DCED !\n");
}


// register device
static struct usb_driver input_driver = {
 .name = "inputDriver",
 .id_table = definition_table,
 .probe = handle_probe,
 .disconnect = handle_disconnect,
};

int init_module(void)
{
	printk(KERN_INFO "Hello world !\n");

	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	int result = usb_register(&input_driver);
	if (result)
		printk(KERN_INFO "Usb register failed !\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Cleaning up module.\n");
	usb_deregister(&input_driver);
}
