#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
	int sockfd;
	int connected;
	socklen_t sizeof_server;
	socklen_t sizeof_client;
	struct sockaddr_in server, client;

	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	sizeof_server = sizeof(server);

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connected = connect(sockfd, (const struct sockaddr*)&server, sizeof_server);
	if(connected < 0){
		perror("connect");
	}
	char greetings[50] = "hello";
	size_t sizeofmsg = sizeof(greetings);
	if(send(sockfd, greetings, sizeofmsg, 0) < 0)
		perror("send");
	if(recv(sockfd, greetings, sizeofmsg, 0) < 0)
		perror("recv");
	printf("%s\n", greetings);
	close(sockfd);
	return 0;
}