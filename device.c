/**
 * device.c - /dev/42module_keyboard file configration
*/
#include <linux/miscdevice.h>
#include <linux/cdev.h> /* cdev_add, cdev_init */
#include <linux/device.h>
#include <linux/fs.h> /* register_chrdev, unregister_chrdev */
#include <linux/seq_file.h> /* seq_read, seq_lseek, single_release */
#include "42kb.h"

#define DEV_NAME "ft_module_keyboard"

static int ft_module_keyboard_open(struct inode *, struct file *);
static ssize_t ft_module_keyboard_read(struct file *, char *, size_t, loff_t *);
static ssize_t ft_module_keyboard_write(struct file *, const char *, size_t, loff_t *);
char *data = 0;
static struct miscdevice ft_module_keyboard_dev;
static struct file_operations ft_module_keyboard_dev_fops = {
	.read = ft_module_keyboard_read,
	.write = ft_module_keyboard_write,
	.open = ft_module_keyboard_open,
};

// file operations
int ft_module_keyboard_open(struct inode * node, struct file * file)
{
	ft_log("Misc device opened");
	return 0;
}

ssize_t ft_module_keyboard_read(struct file *file, char *buff, size_t, loff_t * offset)
{
	ft_log("Misc device read");
	return 0;
}


ssize_t ft_module_keyboard_write(struct file *file, char *buff, size_t, loff_t * offset)
{
	ft_log("Misc device written");
	return 0;
}

int ft_create_misc_device(char *init_data)
{
	ft_module_keyboard_dev.minor = MISC_DYNAMIC_MINOR;
    ft_module_keyboard_dev.name = DEV_NAME;
	ft_module_keyboard_dev.file_operations = &ft_module_keyboard_dev_fops;
	return misc_register(&ft_module_keyboard_dev);
}

int ft_destroy_misc_device(void)
{
	return misc_deregister(&ft_module_keyboard_dev);
}