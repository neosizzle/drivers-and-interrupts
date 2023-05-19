#ifndef __42KB__H__
#define __42KB__H__

#include <linux/list.h>

#define KB_IRQ 1
#define KB_PORT 0x60
#define KEY_DOWN 0
#define KEY_UP 1


#define DEV_NAME "ft_module_keyboard"
#define DRV_NAME "ft_module_keyboard_driver"

struct test { 
	int gay;
	struct list_head list;
};

// USB config (hot-plugging)
int ft_register_usb(void);
void ft_deregister_usb(void);

// Utilities
void ft_log(char *str);
void ft_warn(char *str);

// Misc device handling
int ft_create_misc_device(struct  test* _keylogger);
void ft_destroy_misc_device(void);

// interrupt handling
int ft_register_interrupt(struct test* _event_list);
void ft_deregister_interrupt(void);

#endif  //!__42KB__H__