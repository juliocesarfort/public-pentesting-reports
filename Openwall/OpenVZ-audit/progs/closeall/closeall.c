#include <unistd.h>
#include <errno.h>

#ifdef __linux__
#include <linux/limits.h>
#else
#define NR_OPEN 1024
#endif

int close_all(void)
{
	int fd, max, err;

	max = sysconf(_SC_OPEN_MAX);
	err = max <= 0;

	if (max < NR_OPEN)
		max = NR_OPEN;

	for (fd = 3; fd < max; fd++)
		err |= close(fd) && errno != EBADF;

	return -err;
}
