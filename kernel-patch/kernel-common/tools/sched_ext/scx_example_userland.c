/* SPDX-License-Identifier: GPL-2.0 */
/*
 * A demo sched_ext user space scheduler which provides vruntime semantics
 * using a simple ordered-list implementation.
 *
 * Each CPU in the system resides in a single, global domain. This precludes
 * the need to do any load balancing between domains. The scheduler could
 * easily be extended to support multiple domains, with load balancing
 * happening in user space.
 *
 * Any task which has any CPU affinity is scheduled entirely in BPF. This
 * program only schedules tasks which may run on any CPU.
 *
 * Copyright (c) 2022 Meta Platforms, Inc. and affiliates.
 * Copyright (c) 2022 Tejun Heo <tj@kernel.org>
 * Copyright (c) 2022 David Vernet <dvernet@meta.com>
 */