#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define DEVNAME "tmpdev"

static void fuzzer(mode_t type)
{
	mode_t mode = type | (S_IRUSR | S_IWUSR);
	unsigned int major, minor;
	int retval, saved_errno;

	unlink(DEVNAME);

	for (major = 0; major < 1024; major++)
	for (minor = 0; minor < 256; minor++) {
		retval = mknod(DEVNAME, mode, makedev(major, minor));
		if (retval == -1) {
			saved_errno = errno;
			unlink(DEVNAME);
			printf("mknod %c %u %u = -1 errno=%d (\"%s\")\n",
				"cb"[type == S_IFBLK], major, minor,
				saved_errno, strerror(saved_errno));
			continue;
		}

		retval = open(DEVNAME, O_RDONLY | O_NOCTTY);
		saved_errno = errno;
		unlink(DEVNAME);
		if (retval >= 0)
			close(retval);

		printf("open %c %u %u = %d",
			"cb"[type == S_IFBLK], major, minor, retval);
		if (retval == -1)
			printf(" errno=%d (\"%s\")",
				saved_errno, strerror(saved_errno));
		putchar('\n');
	}
}

int main(void)
{
	fuzzer(S_IFCHR);
	fuzzer(S_IFBLK);
	return 0;
}
