/**
 * device.c - /dev/42module_keyboard file configration
*/
#include <linux/miscdevice.h>
#include <linux/cdev.h> /* cdev_add, cdev_init */
#include <linux/device.h>
#include <linux/fs.h> /* register_chrdev, unregister_chrdev */
#include <linux/seq_file.h> /* seq_read, seq_lseek, single_release */
#include "42kb.h"

DEFINE_SPINLOCK(devfile_io_spinlock);
static int ft_module_keyboard_open(struct inode *, struct file *);
static ssize_t ft_module_keyboard_read(struct file *, char *, size_t, loff_t *);
static ssize_t ft_module_keyboard_write(struct file *, const char *, size_t, loff_t *);
static struct miscdevice ft_module_keyboard_dev;
static struct file_operations ft_module_keyboard_dev_fops = {
	.read = ft_module_keyboard_read,
	.write = ft_module_keyboard_write,
	.open = ft_module_keyboard_open,
};

// file operations
static int ft_module_keyboard_open(struct inode * node, struct file * file)
{
	ft_log("Misc device opened");
	
	// add new test struct at tail of list
	
	return 0;
}

static ssize_t ft_module_keyboard_read(struct file *file, char *buff, size_t, loff_t * offset)
{
	struct list_head *head_ptr;
	struct event_struct *entry;
	char *output_str;
	char *temp_str;
	int did_not_cpy;
	
	ft_log("Misc device read");
	spin_lock(&devfile_io_spinlock);
	output_str = kmalloc(69420 * 42, GFP_KERNEL);
	output_str[0] = 0;
	head_ptr = g_driver->events_head->list.next;
	while (head_ptr != &(g_driver->events_head->list))
	{
		entry = list_entry(head_ptr, struct event_struct, list);

		temp_str = event_to_str(*entry);
		strcpy(output_str + strlen(output_str), temp_str);
		kfree(temp_str);

		head_ptr = head_ptr->next;
	}
	spin_unlock(&devfile_io_spinlock);
	if (*offset == strlen(output_str))
	{
		kfree(output_str);
		return 0;
	}

	did_not_cpy = copy_to_user(buff, output_str, strlen(output_str));
	*offset = strlen(output_str);
	return strlen(output_str) - did_not_cpy;
}


static ssize_t ft_module_keyboard_write(struct file * file, const char *buff, size_t, loff_t *offset)
{
	ft_log("Misc device written");
	return 0;
}

int ft_create_misc_device(void)
{
	ft_module_keyboard_dev.minor = MISC_DYNAMIC_MINOR;
    ft_module_keyboard_dev.name = DEV_NAME;
	ft_module_keyboard_dev.fops = &ft_module_keyboard_dev_fops;
	return misc_register(&ft_module_keyboard_dev);
}

void ft_destroy_misc_device(void)
{
	misc_deregister(&ft_module_keyboard_dev);
}