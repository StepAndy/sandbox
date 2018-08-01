#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{	
	int pipefd;
	char *message;
	message = malloc(50);
	if(mkfifo("named pipe", 0744) == -1){
		perror("mkfifo");
	}
	pipefd = open("named pipe", O_WRONLY );
	strcpy(message,"HHHHlloDlrow!");
	write(pipefd, message, sizeof(50));
	close(pipefd);

	return 0;
}