//TCP
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int G1, G2;

void sig_int(int errno)
{
	close(G1);
	close(G2);
}

int main(int argc, char const *argv[])
{
	int sockfd;
	int binded;
	int listens;
	int acceptfd;
	socklen_t sizeof_server;
	socklen_t sizeof_client;
	
	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	sizeof_server = sizeof(server);

	signal(SIGINT, sig_int);

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockfd < 0){
		perror("socket");
	}
	G1 = sockfd;
	binded = bind(sockfd, (const struct sockaddr*)&server, sizeof_server);
	if(!binded){
		perror("bind");
	}
	listens = listen(sockfd, 5);
	if(!listens){
		perror("listen");
	}
	acceptfd = accept(sockfd, (struct sockaddr*)&client, &sizeof_client);
	if(acceptfd < 0){
		perror("accept");
	}
	G2 = acceptfd;
	char message[50];
	if(recv(acceptfd, message, 50, 0) < 0)
		perror("recv");
	printf("%s\n", message);
	message[2] = 'E';
	message[3] = 'e';
	if(send(acceptfd, message, 50, 0) < 0)
		perror("send");
	close(acceptfd);
	close(sockfd);
	return 0;
}