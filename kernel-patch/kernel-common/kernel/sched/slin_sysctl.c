/* SPDX-License-Identifier: GPL-2.0 */

#include "slim.h"

unsigned int
unsigned int

#define HIGHRES_TICK_CTRL
#define HIGHRES_TICK_CTRL_DBG

#define SLIM_SCHED_DIR


noinline int tracing_mark_write(const char *buf)
{
}


static char *files_name[] = {

};

static int *file_data[] = {

};

static ssize_t slim_common_write(struct file *file, const char __user *buf,
                               size_t count, loff_t *ppos)
{

}

static int slim_common_show(struct seq_file *m, void *v)
{

}

static int slim_common_open(struct inode *inode, struct file *file)
{

}

static const struct proc_ops common_proc_ops = {

};

struct proc_dir_entry *slim_dir;
EXPORT_SYMBOL(slim_dir);

static int __init slim_sysfs_init(void)
{

}

__initcall(slim_sysfs_init);