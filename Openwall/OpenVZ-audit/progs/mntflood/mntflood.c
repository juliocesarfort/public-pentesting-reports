#include <stdio.h>
#include <sys/mount.h>

int main(void)
{
	while (1) {
		if (mount("/root", "/mnt", "bind", MS_MGC_VAL|MS_BIND, NULL))
			perror("mount");
	}

	return 0;
}
