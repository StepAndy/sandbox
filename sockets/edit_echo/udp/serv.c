#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
	int sockfd;
	int binded;
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
	binded = bind(sockfd, (struct sockaddr*)&server, sizeof_server);
	if(!binded){
		perror("bind");
	}
	
	socklen_t sizeof_client;
	sizeof_client = sizeof(client);
	char buf[50];
	size_t sizeof_buf = sizeof(buf);
	if(recvfrom(sockfd, buf, sizeof_buf, 0, (struct sockaddr*)&client, &sizeof_client) < 0){
		perror("recv");
	}
	printf("received [%s]\n", buf);
	buf[1] = 'i';
	buf[2] = 'o';
	if(sendto(sockfd, buf, sizeof_buf, 0, (struct sockaddr*)&client, sizeof_client) < 0){
		perror("send");
	}
	
	close(sockfd);
	return 0;
}