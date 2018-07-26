#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int pipefd;
	char *message = malloc(500);
	pipefd = open("named pipe", O_RDONLY );
	read(pipefd, message, 500);
	printf("[Message is]:\n%s\n", message);
	close(pipefd);
	unlink("named pipe");
	return 0;
}