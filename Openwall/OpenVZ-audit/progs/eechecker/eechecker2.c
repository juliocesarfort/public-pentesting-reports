#define MODULE
#define __KERNEL__
#define _LOOSE_KERNEL_NAMES
#define __SMP__
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

int init_module(void)
{
	struct task_struct *task;

	for_each_process_all(task) {
		printk("pid=%u ve_task_info=%p exec_env=%p "
			"task_bc=%p exec_ub=%p\n",
			task->pid,
			VE_TASK_INFO(task),
			VE_TASK_INFO(task)->exec_env,
			task_bc(task),
			task_bc(task)->exec_ub);
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
