/* Copyright (c) Meta Platforms, Inc. and affiliates. */
/*
 * This software may be used and distributed according to the terms of the
 * GNU General Public License version 2.
 *
 * Atropos is a multi-domain BPF / userspace hybrid scheduler where the BPF
 * part does simple round robin in each domain and the userspace part
 * calculates the load factor of each domain and tells the BPF part how to load
 * balance the domains.
 *
 * Every task has an entry in the task_data map which lists which domain the
 * task belongs to. When a task first enters the system (atropos_prep_enable),
 * they are round-robined to a domain.
 *
 * atropos_select_cpu is the primary scheduling logic, invoked when a task
 * becomes runnable. The lb_data map is populated by userspace to inform the BPF
 * scheduler that a task should be migrated to a new domain. Otherwise, the task
 * is scheduled in priority order as follows:
 * * The current core if the task was woken up synchronously and there are idle
 *   cpus in the system
 * * The previous core, if idle
 * * The pinned-to core if the task is pinned to a specific core
 * * Any idle cpu in the domain
 *
 * If none of the above conditions are met, then the task is enqueued to a
 * dispatch queue corresponding to the domain (atropos_enqueue).
 *
 * atropos_dispatch will attempt to consume a task from its domain's
 * corresponding dispatch queue (this occurs after scheduling any tasks directly
 * assigned to it due to the logic in atropos_select_cpu). If no task is found,
 * then greedy load stealing will attempt to find a task on another dispatch
 * queue to run.
 *
 * Load balancing is almost entirely handled by userspace. BPF populates the
 * task weight, dom mask and current dom in the task_data map and executes the
 * load balance based on userspace populating the lb_data map.
 */
