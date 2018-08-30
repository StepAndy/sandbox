#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void sig_usr1(int errno)
{
	printf("bye!");
	sleep(5);
	exit(0);
}

int main(int argc, char const *argv[])
{
	int a=0;
	sigset_t mask;
	sigaddset(&mask, SIGUSR1);
	signal(SIGUSR1, sig_usr1);
	printf("pid = [%d]\n", getpid());
	while(1){
		a++;
		//sleep(1);
		printf("%d\n", a);
		sigsuspend(&mask);
	}
	return 0;
}