/* SPDX-License-Identifier: GPL-2.0 */
/*
 * A central FIFO sched_ext scheduler which demonstrates the followings:
 *
 * a. Making all scheduling decisions from one CPU:
 *
 *    The central CPU is the only one making scheduling decisions. All other
 *    CPUs kick the central CPU when they run out of tasks to run.
 *
 *    There is one global BPF queue and the central CPU schedules all CPUs by
 *    dispatching from the global queue to each CPU's local dsq from dispatch().
 *    This isn't the most straightforward. e.g. It'd be easier to bounce
 *    through per-CPU BPF queues. The current design is chosen to maximally
 *    utilize and verify various SCX mechanisms such as LOCAL_ON dispatching.
 *
 * b. Tickless operation
 *
 *    All tasks are dispatched with the infinite slice which allows stopping the
 *    ticks on CONFIG_NO_HZ_FULL kernels running with the proper nohz_full
 *    parameter. The tickless operation can be observed through
 *    /proc/interrupts.
 *
 *    Periodic switching is enforced by a periodic timer checking all CPUs and
 *    preempting them as necessary. Unfortunately, BPF timer currently doesn't
 *    have a way to pin to a specific CPU, so the periodic timer isn't pinned to
 *    the central CPU.
 *
 * c. Preemption
 *
 *    Kthreads are unconditionally queued to the head of a matching local dsq
 *    and dispatched with SCX_DSQ_PREEMPT. This ensures that a kthread is always
 *    prioritized over user threads, which is required for ensuring forward
 *    progress as e.g. the periodic timer may run on a ksoftirqd and if the
 *    ksoftirqd gets starved by a user thread, there may not be anything else to
 *    vacate that user thread.
 *
 *    SCX_KICK_PREEMPT is used to trigger scheduling and CPUs to move to the
 *    next tasks.
 *
 * This scheduler is designed to maximize usage of various SCX mechanisms. A
 * more practical implementation would likely put the scheduling loop outside
 * the central CPU's dispatch() path and add some form of priority mechanism.
 *
 * Copyright (c) 2022 Meta Platforms, Inc. and affiliates.
 * Copyright (c) 2022 Tejun Heo <tj@kernel.org>
 * Copyright (c) 2022 David Vernet <dvernet@meta.com>
 */
