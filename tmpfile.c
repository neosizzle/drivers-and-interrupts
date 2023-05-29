/**
 * tmpfile.c - /tmp/42module_keyboard file configration
*/
#include "42kb.h"
#include <linux/fs.h>

struct file* tmpfile = 0;

// TODO write to tmpfile

int ft_create_tmpfile(void)
{
	tmpfile = filp_open("/tmp/lol", O_RDONLY | O_CREAT, S_IRWXU);
	if (tmpfile) {
		ft_log("Created tmpfile\n");
		filp_close(tmpfile, NULL);
		return 0;
	}
	else
	{
		ft_warn("Cannot create tmpfile");
		return 1;
	}
}

// TODO unlink tmpfile
void ft_destroy_tmpfile(void)
{
	struct inode *parent_inode;
	char *parent_name;

	if (!tmpfile) return;
	parent_inode = tmpfile->f_path.dentry->d_parent->d_inode;
	parent_name = tmpfile->f_path.dentry->d_parent->d_name.name;
	// if (file_count(tmpfile) > 0)
	printk("parent got\n");
	filp_close(tmpfile, NULL);
	if (!parent_inode) return;
	inode_lock(parent_inode);
	printk("unlinking parent %s wtih destination %s\n",parent_name ,tmpfile->f_path.dentry->d_name.name);
	vfs_unlink(NULL, parent_inode, tmpfile->f_path.dentry, NULL);
	inode_unlock(parent_inode);
	printk("vfs unlinked\n");
}