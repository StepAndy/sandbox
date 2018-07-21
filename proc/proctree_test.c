#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t first, second = 2, third;
	first = fork();
	if (first == 0) {
		printf("child %d\n", second);
		second = 3;
		printf("child %d\n", second);
	}
	else {
		first = getpid();
		printf("%d\n", second);	
	}

	if (getpid() == first) printf("NANK\n");
	return 0;
}