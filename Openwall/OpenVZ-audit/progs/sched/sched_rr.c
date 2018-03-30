#include <stdio.h>
#include <unistd.h>
#include <sched.h>

int main(int argc, char **argv)
{
	struct sched_param param;

	if (argc < 2) {
		printf("Usage: %s COMMAND\n", argv[0]);
		return 1;
	}

	param.sched_priority = 1;
	if (sched_setscheduler(getpid(), SCHED_RR, &param)) {
		perror("sched_setscheduler");
		return 1;
	}

	execv(argv[1], argv + 1);

	perror("execv");
	return 1;
}
