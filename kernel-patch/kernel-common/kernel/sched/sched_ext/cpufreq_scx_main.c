// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024 Oplus. All rights reserved.
 */

struct cpufreq_governor cpufreq_scx_gov = {
	.name			= "scx",
	.owner			= THIS_MODULE,
	.flags			= CPUFREQ_GOV_DYNAMIC_SWITCHING,
	.init			= scx_gov_init,
	.exit			= scx_gov_exit,
	.start			= scx_gov_start,
	.stop			= scx_gov_stop,
	.limits			= scx_gov_limits,
};

#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_SCX
struct cpufreq_governor *cpufreq_default_governor(void)
{
	return &cpufreq_scx_gov;
}
#endif


void scx_gov_sysctl_init(void)
{

}

int scx_cpufreq_init(void)
{

}
