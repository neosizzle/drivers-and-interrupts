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

int ft_write_tmpfile(char *str)
{
	struct file_operations	*f_op = tmpfile->f_op;

	if (!f_op)
	{
		ft_warn("No fop on tmpfile\n");
		return 1;
	}

	return kernel_write(tmpfile, str, strlen(str), &tmpoffset);
}

int ft_create_tmpfile(void)
{
	tmpfile = filp_open("/tmp/42kb.log", O_WRONLY | O_CREAT, S_IRWXU);
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
	time64_t time;

	time = ktime_get_seconds();
	printk("ITOA   %s\n", ft_itoa(time));
}

void ft_destroy_tmpfile(void)
{
	// struct inode *parent_inode;

	// if (!tmpfile) return;
	// parent_inode = tmpfile->f_path.dentry->d_parent->d_inode;
	// if (!parent_inode) return;

	// inode_lock(parent_inode);
	// vfs_unlink(NULL, parent_inode, tmpfile->f_path.dentry, NULL); // deletes and closes
	// inode_unlock(parent_inode);
}