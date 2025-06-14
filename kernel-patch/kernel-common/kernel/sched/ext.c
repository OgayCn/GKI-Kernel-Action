/* SPDX-License-Identifier: GPL-2.0 */
/*
 * BPF extensible scheduler class: Documentation/scheduler/sched-ext.rst
 *
 * Copyright (c) 2022 Meta Platforms, Inc. and affiliates.
 * Copyright (c) 2022 Tejun Heo <tj@kernel.org>
 * Copyright (c) 2022 David Vernet <dvernet@meta.com>
 */



















/*
 * This can't be done from init_sched_ext_class() as register_btf_kfunc_id_set()
 * needs most of the system to be up.
 */
static int __init register_ext_kfuncs(void)
{

}
__initcall(register_ext_kfuncs);
