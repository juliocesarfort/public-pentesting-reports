#define MODULE
#define __KERNEL__
#define _LOOSE_KERNEL_NAMES
#define __SMP__
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

#define WATCHPID 20538

int init_module(void)
{
	struct task_struct *task;
	unsigned int i;

	task = find_task_by_pid_ve(WATCHPID);
	if (!task)
		return -ESRCH;

	for (i = 0; i < 0x10000000; i++) {
		rmb();
		if (ve_is_super(VE_TASK_INFO(task)->exec_env)) {
			printk("ve_is_super at %u\n", i);
			return -EEXIST;
		}
	}

	return -EAGAIN;
}

void cleanup_module(void)
{
}

#include <linux/vermagic.h>

// MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_LICENSE("GPL");

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = "exec_env_checker",
	.init = init_module,
	.exit = cleanup_module
};
