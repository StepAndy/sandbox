#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t first_pid, second_pid, third_pid,
	fourth_pid, fifth_pid, sixth_pid;
	printf("this is initial %d\n",getpid() );
	first_pid = fork(); 		//1 & 2
	if (first_pid > 0) printf("This is second: %d\n", first_pid);
 	if (first_pid == 0) {		
		second_pid = getpid();	
		printf("This is second in child :%d\n", getpid());
	}
	else if (first_pid > 0) first_pid = fork(); //1 & 3      & 2
	if(first_pid == 0 && getpid() != second_pid) {
		third_pid = getpid();	
	}
	if(getpid() == third_pid) third_pid = fork(); //3 & 4    & 1 & 2
	if(third_pid == 0) {
		fourth_pid = getpid();
	}
	if(third_pid > 0) third_pid = getpid(); //здесь три процесса получают пид в third_pid?

	if(getpid() == second_pid) second_pid = fork(); // 2 & 5   & 1 & 3 & 4
	if(second_pid == 0) fifth_pid = getpid();
	else if(second_pid > 0) second_pid = fork();    // 2 & 6   & 1 & 3 & 4 & 5
	if(second_pid == 0 && getpid() != fifth_pid) {
		sixth_pid = getppid();	
	}
	printf("pid = %d ppid = %d\n", getpid(), getppid());
	

	if(getpid() == first_pid) printf("\n");
	if(getpid() == second_pid) printf("\n");
	if(getpid() == third_pid && getppid() == first_pid) printf("pid=%d\n",getpid());
	if(getpid() == fourth_pid) printf("\n");
	if(getpid() == fifth_pid) printf("\n");
	if(getpid() == sixth_pid) printf("\n");
	return 0;
	}

/*
if(getpid() == second_pid) second_pid = fork();
	if(second_pid == 0) fifth_pid = getpid();
	/*else if(second_pid > 0) second_pid = fork();
	if(second_pid == 0) {
		sixth_pid = getppid();	
	}*/
