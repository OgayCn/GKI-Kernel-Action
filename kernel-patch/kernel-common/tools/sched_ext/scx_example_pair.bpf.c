/* SPDX-License-Identifier: GPL-2.0 */
/*
 * A demo sched_ext core-scheduler which always makes every sibling CPU pair
 * execute from the same CPU cgroup.
 *
 * This scheduler is a minimal implementation and would need some form of
 * priority handling both inside each cgroup and across the cgroups to be
 * practically useful.
 *
 * Each CPU in the system is paired with exactly one other CPU, according to a
 * "stride" value that can be specified when the BPF scheduler program is first
 * loaded. Throughout the runtime of the scheduler, these CPU pairs guarantee
 * that they will only ever schedule tasks that belong to the same CPU cgroup.
 *
 * Scheduler Initialization
 * ------------------------
 *
 * The scheduler BPF program is first initialized from user space, before it is
 * enabled. During this initialization process, each CPU on the system is
 * assigned several values that are constant throughout its runtime:
 *
 * 1. *Pair CPU*: The CPU that it synchronizes with when making scheduling
 *		  decisions. Paired CPUs always schedule tasks from the same
 *		  CPU cgroup, and synchronize with each other to guarantee
 *		  that this constraint is not violated.
 * 2. *Pair ID*:  Each CPU pair is assigned a Pair ID, which is used to access
 *		  a struct pair_ctx object that is shared between the pair.
 * 3. *In-pair-index*: An index, 0 or 1, that is assigned to each core in the
 *		       pair. Each struct pair_ctx has an active_mask field,
 *		       which is a bitmap used to indicate whether each core
 *		       in the pair currently has an actively running task.
 *		       This index specifies which entry in the bitmap corresponds
 *		       to each CPU in the pair.
 *
 * During this initialization, the CPUs are paired according to a "stride" that
 * may be specified when invoking the user space program that initializes and
 * loads the scheduler. By default, the stride is 1/2 the total number of CPUs.
 *
 * Tasks and cgroups
 * -----------------
 *
 * Every cgroup in the system is registered with the scheduler using the
 * pair_cgroup_init() callback, and every task in the system is associated with
 * exactly one cgroup. At a high level, the idea with the pair scheduler is to
 * always schedule tasks from the same cgroup within a given CPU pair. When a
 * task is enqueued (i.e. passed to the pair_enqueue() callback function), its
 * cgroup ID is read from its task struct, and then a corresponding queue map
 * is used to FIFO-enqueue the task for that cgroup.
 *
 * If you look through the implementation of the scheduler, you'll notice that
 * there is quite a bit of complexity involved with looking up the per-cgroup
 * FIFO queue that we enqueue tasks in. For example, there is a cgrp_q_idx_hash
 * BPF hash map that is used to map a cgroup ID to a globally unique ID that's
 * allocated in the BPF program. This is done because we use separate maps to
 * store the FIFO queue of tasks, and the length of that map, per cgroup. This
 * complexity is only present because of current deficiencies in BPF that will
 * soon be addressed. The main point to keep in mind is that newly enqueued
 * tasks are added to their cgroup's FIFO queue.
 *
 * Dispatching tasks
 * -----------------
 *
 * This section will describe how enqueued tasks are dispatched and scheduled.
 * Tasks are dispatched in pair_dispatch(), and at a high level the workflow is
 * as follows:
 *
 * 1. Fetch the struct pair_ctx for the current CPU. As mentioned above, this is
 *    the structure that's used to synchronize amongst the two pair CPUs in their
 *    scheduling decisions. After any of the following events have occurred:
 *
 * - The cgroup's slice run has expired, or
 * - The cgroup becomes empty, or
 * - Either CPU in the pair is preempted by a higher priority scheduling class
 *
 * The cgroup transitions to the draining state and stops executing new tasks
 * from the cgroup.
 *
 * 2. If the pair is still executing a task, mark the pair_ctx as draining, and
 *    wait for the pair CPU to be preempted.
 *
 * 3. Otherwise, if the pair CPU is not running a task, we can move onto
 *    scheduling new tasks. Pop the next cgroup id from the top_q queue.
 *
 * 4. Pop a task from that cgroup's FIFO task queue, and begin executing it.
 *
 * Note again that this scheduling behavior is simple, but the implementation
 * is complex mostly because this it hits several BPF shortcomings and has to
 * work around in often awkward ways. Most of the shortcomings are expected to
 * be resolved in the near future which should allow greatly simplifying this
 * scheduler.
 *
 * Dealing with preemption
 * -----------------------
 *
 * SCX is the lowest priority sched_class, and could be preempted by them at
 * any time. To address this, the scheduler implements pair_cpu_release() and
 * pair_cpu_acquire() callbacks which are invoked by the core scheduler when
 * the scheduler loses and gains control of the CPU respectively.
 *
 * In pair_cpu_release(), we mark the pair_ctx as having been preempted, and
 * then invoke:
 *
 * scx_bpf_kick_cpu(pair_cpu, SCX_KICK_PREEMPT | SCX_KICK_WAIT);
 *
 * This preempts the pair CPU, and waits until it has re-entered the scheduler
 * before returning. This is necessary to ensure that the higher priority
 * sched_class that preempted our scheduler does not schedule a task
 * concurrently with our pair CPU.
 *
 * When the CPU is re-acquired in pair_cpu_acquire(), we unmark the preemption
 * in the pair_ctx, and send another resched IPI to the pair CPU to re-enable
 * pair scheduling.
 *
 * Copyright (c) 2022 Meta Platforms, Inc. and affiliates.
 * Copyright (c) 2022 Tejun Heo <tj@kernel.org>
 * Copyright (c) 2022 David Vernet <dvernet@meta.com>
 */