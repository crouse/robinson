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

#define STR_LEN sizeof(Test)

int main()
{
	int socketFD;
	int ret;
	char buf[STR_LEN];

	signal(SIGPIPE,SIG_IGN);
	Test p;
	memset(&p,0,sizeof(Test));
	struct sockaddr_in addr;

	socketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (-1 == socketFD)
	{
	  perror("create socket error");
	  exit(EXIT_FAILURE);
	}

	memset(&addr, 0, sizeof(struct sockaddr_in));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);

	ret = inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	connect(socketFD, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in));

	memset(buf,0x00, STR_LEN);

	ret = read(socketFD, buf, sizeof(buf));
 
	memcpy(&p, &buf, sizeof(p));
	printf("Received: id = %d, name = %s, address = %s, phoneNumber = %s\n",
			p.id, p.name, p.address, p.phoneNumber);

	shutdown(socketFD, SHUT_RDWR);
	close(socketFD);

	return 0;
}
