#include <stdio.h>
#include <sys/mount.h>

int main(int argc, char **argv)
{
	if (argc != 4) return 1;

	if (mount(argv[1], argv[2], argv[3], MS_MGC_VAL, NULL))
		perror("mount");

	return 0;
}
