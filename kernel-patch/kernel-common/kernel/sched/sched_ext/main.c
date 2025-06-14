// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024 Oplus. All rights reserved.
 */

extern int scx_init(void);
extern void scx_exit(void);


static int __init hmbird_common_init(void)
{

}

static void __exit hmbird_common_exit(void)
{

}

module_init(hmbird_common_init);
module_exit(hmbird_common_exit);
MODULE_LICENSE("GPL v2");