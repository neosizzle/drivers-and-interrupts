#ifndef __42KB__H__
#define __42KB__H__

// USB config (hot-plugging)
int ft_register_usb(void);
void ft_deregister_usb(void);

// Utilities
void ft_log(char *str);
void ft_warn(char *str);

#endif  //!__42KB__H__