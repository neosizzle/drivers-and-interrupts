/**
 * device.c - /dev/42module_keyboard file configration
*/
#include <linux/miscdevice.h>
#include <linux/cdev.h> /* cdev_add, cdev_init */
#include <linux/device.h>
#include <linux/fs.h> /* register_chrdev, unregister_chrdev */
#include <linux/seq_file.h> /* seq_read, seq_lseek, single_release */
#include "42kb.h"


static int ft_module_keyboard_open(struct inode *, struct file *);
static ssize_t ft_module_keyboard_read(struct file *, char *, size_t, loff_t *);
static ssize_t ft_module_keyboard_write(struct file *, const char *, size_t, loff_t *);
static struct miscdevice ft_module_keyboard_dev;
static struct file_operations ft_module_keyboard_dev_fops = {
	.read = ft_module_keyboard_read,
	.write = ft_module_keyboard_write,
	.open = ft_module_keyboard_open,
};
char *data = 0;
struct test* keylogger;

// file operations
static int ft_module_keyboard_open(struct inode * node, struct file * file)
{
	ft_log("Misc device opened");
	
	// add new test struct at tail of list
	
	return 0;
}

static ssize_t ft_module_keyboard_read(struct file *file, char *buff, size_t, loff_t * offset)
{
	ft_log("Misc device read");

	// iterates thru linked list and print elements
	struct list_head *ptr;
	struct test *entry;
	ptr = &(keylogger->list);
	do
	{
		entry = list_entry(ptr, struct test, list);
		printk("[42kb] entry is %d\n", entry->gay);
		ptr = ptr->next;
	} while (ptr != &(keylogger->list));
	
	
	return 0;
}


static ssize_t ft_module_keyboard_write(struct file * file, const char *buff, size_t, loff_t *offset)
{
	ft_log("Misc device written");
	return 0;
}

int ft_create_misc_device(struct  test* _keylogger)
{
	ft_module_keyboard_dev.minor = MISC_DYNAMIC_MINOR;
    ft_module_keyboard_dev.name = DEV_NAME;
	ft_module_keyboard_dev.fops = &ft_module_keyboard_dev_fops;
	keylogger = _keylogger;
	return misc_register(&ft_module_keyboard_dev);
}

void ft_destroy_misc_device(void)
{
	misc_deregister(&ft_module_keyboard_dev);
}