#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#define PORT 7000

typedef struct Test {
	int id;
	char name[32];
	char address[64];
	char phoneNumber[16];
} Test;

int main()
{
	int ret;
	pid_t pid;
	int connectFD;
	int socketFD;
	signal(SIGPIPE,SIG_IGN);

	Test p;
	p.id = 1;

	snprintf(p.name, 32, "lei");
	snprintf(p.address, 64, "ChangPing, HuiLongGuan");
	snprintf(p.phoneNumber, 32, "11101620835");

	struct sockaddr_in addr;
	socketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(-1 == socketFD) {
	  perror("create socket error");
	  exit(EXIT_FAILURE);
	}

	memset(&addr, 0, sizeof(struct sockaddr_in));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(7000);
	addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(socketFD, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in));

	if (-1 == ret) {
	  perror("bind error");
	  close(socketFD);
	  exit(EXIT_FAILURE);
	}

	ret = listen(socketFD, 10);

	if (-1 == ret) {
		perror("listen error");
		close(socketFD);
		exit(EXIT_FAILURE);
	}

	for(;;) {

		connectFD = accept(socketFD, NULL, NULL);

		if (-1 == connectFD) {
			perror("accept error");
			close(socketFD);
			exit(EXIT_FAILURE);
		}

		send(connectFD, &p, sizeof(p), 0);

		printf("Send: id = %d, name = %s, address = %s, phoneNumber = %s\n", 
				p.id, p.name, p.address, p.phoneNumber);

		shutdown(connectFD, SHUT_RDWR);

		close(connectFD);
	}

	close(socketFD);

	return 0;
}
