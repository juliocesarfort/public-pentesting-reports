#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

int main(void)
{
	int sock;
	struct ifreq ifr;
	uint32_t addr;

	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0) {
		perror("socket");
		return 1;
	}

	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = IFF_UP | IFF_POINTOPOINT | IFF_RUNNING | IFF_NOARP;
	ifr.ifr_addr.sa_family = AF_INET;

	for (addr = 1; addr < 0x01000000; addr++) {
		sprintf(ifr.ifr_name, "venet0:%u", addr);
		((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr = htonl(addr);
		if ((addr & 0xff) == 0)
			printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
		if (ioctl(sock, SIOCSIFADDR, &ifr) < 0)
			perror("ioctl");
	}

	return 0;
}
