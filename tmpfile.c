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
		printk("opened file\n");
		filp_close(tmpfile, NULL);
		return 0;
	}
	else
	{
		printk("cannot open file\n");
		return 1;
	}
}

// TODO unlink tmpfile
void ft_destroy_tmpfile(void)
{
	struct inode *parent_inode;

	if (!tmpfile) return;
	filp_close(tmpfile, NULL);
	parent_inode = tmpfile->f_path.dentry->d_parent->d_inode;
	if (!parent_inode) return;
	printk("parent node obtainable\n");
	// inode_lock(parent_inode);
	// // vfs_unlink(parent_inode, tmpfile->f_path.dentry, NULL); 
	// vfs_unlink(NULL, parent_inode, tmpfile->f_path.dentry, NULL);   
	// inode_unlock(parent_inode);
}