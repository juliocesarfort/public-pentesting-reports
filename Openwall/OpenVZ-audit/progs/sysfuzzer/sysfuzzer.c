#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <linux/unistd.h>

static long sys_any(long num, long args[5])
{
	#define __NR_any5 num
	_syscall5(long, any5,
		long, arg1, long, arg2, long, arg3, long, arg4, long, arg5);

	return any5(args[0], args[1], args[2], args[3], args[4]);
}

static void fuzzer(void)
{
	long args[5];
	long num, retval;

	memset(args, 0, sizeof(args));

	for (num = 0; num < 1024; num++) {
		switch (num) {
		case __NR_exit:
		case __NR_fork:
		case __NR_pause:
		case __NR_sigsuspend:
		case __NR_sigreturn:
		case __NR_clone:
		case __NR__newselect:
		case __NR_rt_sigreturn:
		case __NR_vfork:
		case __NR_exit_group:
			/* harmful to the fuzzer, but no VPS specifics */
			continue;
		case __NR_reboot:
		case __NR_vhangup:
			/* source code audit only, no fuzzing */
			continue;
		}
		retval = sys_any(num, args);
		printf("SYS_%ld() = %ld", num, retval);
		if (retval == -1)
			printf(" errno=%d (\"%s\")", errno, strerror(errno));
		putchar('\n');
	}
}

int main(void)
{
	setbuf(stdout, NULL);
	fuzzer();
	return 0;
}
