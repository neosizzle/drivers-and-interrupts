#ifndef __42KB__H__
#define __42KB__H__

// USB config (hot-plugging)
int ft_register_usb(void);
void ft_deregister_usb(void);

// Utilities
void ft_log(char *str);
void ft_warn(char *str);

// Misc device handling
int ft_create_misc_device(char *init_data);
int ft_destroy_misc_device(void);

#endif  //!__42KB__H__