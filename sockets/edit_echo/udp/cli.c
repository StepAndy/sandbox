#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
	int sockfd;
	int connected;
	socklen_t sizeof_server;

	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port = htons(9090);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	sizeof_server = sizeof(server);
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sockfd < 0){
		perror("socket");
	}
	connected = connect(sockfd, (struct sockaddr*)&server, sizeof_server);
	if(connected < 0){
		perror("connect");
	}
	char buf[50] = "hello";
	size_t sizeof_buf = sizeof(buf);
	send(sockfd, buf, sizeof_buf, 0);
	recv(sockfd, buf, sizeof_buf, 0);
	printf("received [%s]\n", buf);
	close(sockfd);
	return 0;
}