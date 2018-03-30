#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

static void print_data(unsigned char *data, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		printf("%02x%c", (int)data[i],
			i < count - 1 && i % 24 != 23 ? ' ' : '\n');
	}
}

int main(int argc, char **argv)
{
	char buffer[1600];
	int in, size;

	if (argc != 4) return 1;

	if ((in = socket(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]))) < 0) {
		perror("socket");
		return 1;
	}

	setbuf(stdout, NULL);

	alarm(1);

	while (1) {
		size = read(in, buffer, sizeof(buffer));
		print_data(buffer, size);
	}
}
