// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024 Oplus. All rights reserved.
 */
 
#include <linux/module.h>
#include <linux/init.h>

extern int scx_init(void);
extern void scx_exit(void);


static int __init hmbird_common_init(void)
{
    return scx_init();
}

static void __exit hmbird_common_exit(void)
{
    scx_exit();
}

module_init(hmbird_common_init);
module_exit(hmbird_common_exit);
MODULE_LICENSE("GPL v2");