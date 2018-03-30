#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/route.h>

int main(void)
{
	int sock;
	struct rtentry rt;
	uint32_t addr;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		return 1;
	}

	memset(&rt, 0, sizeof(rt));
	rt.rt_flags = RTF_UP | RTF_HOST;
	rt.rt_dev = "venet0";
	rt.rt_dst.sa_family = AF_INET;

	for (addr = 0; addr < 0x01000000; addr++) {
		((struct sockaddr_in *)&rt.rt_dst)->sin_addr.s_addr = htonl(addr);
		if ((addr & 0xff) == 0)
			printf("%s\n", inet_ntoa(((struct sockaddr_in *)&rt.rt_dst)->sin_addr));
		if (ioctl(sock, SIOCADDRT, &rt) < 0)
			perror("ioctl");
	}

	return 0;
}
