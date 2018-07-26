#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
	pid_t pid;
	int echo_pipe[2];
	pipe(echo_pipe);
	if((pid = fork()) == 0){
		char *short_message_from_the_parent = malloc(25);
		close(echo_pipe[1]);
		read(echo_pipe[0], short_message_from_the_parent, 25);
		printf("%s\n", short_message_from_the_parent);
	}
	else if(pid > 0){
		char message_for_the_child[] = "Hello,World!";
		close(echo_pipe[0]);
		write(echo_pipe[1], message_for_the_child, sizeof(message_for_the_child));
	}
	else if(pid == -1){
		perror("fork");
	}


	return 0;
}