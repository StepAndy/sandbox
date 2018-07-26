#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	pid_t first_pid, second_pid, third_pid,
		  fourth_pid, fifth_pid, sixth_pid;

	//Переменные для хранения результатов fork участвующих в нем процессов
	pid_t first_to_second_forked_result, 
		  first_to_third_forked_result,
		  second_to_fifth_forked_result,
		  second_to_sixth_forked_result, 
		  third_to_fourth_forked_result;

	//Создаю ответвление от первого ко второму, от первого к третьему
	first_to_second_forked_result = fork();
	if(first_to_second_forked_result == 0) second_pid = getpid();
	else {
		first_pid = getpid();
		first_to_third_forked_result = fork();
		if(first_to_third_forked_result == 0) third_pid = getpid();	
		else wait(0);//
	}
	
	//Создаю ответвление от третьего к четвертому
	if(getpid() == third_pid) {
		third_to_fourth_forked_result = fork();
		if(third_to_fourth_forked_result == 0) fourth_pid = getpid();
		else wait(0);//
	}

	//Создаю ответвление от второго к пятому, от второго к шестому
	if(getpid() == second_pid) {
		second_to_fifth_forked_result = fork();
		if(second_to_fifth_forked_result == 0) fifth_pid = getpid();
		else {
			second_to_sixth_forked_result = fork();
			if (second_to_sixth_forked_result == 0) sixth_pid = getpid();
			else wait(0);	//
		}
	}

	if(getpid() == first_pid) printf("1 pid=%d, 1 ppid=%d\n",getpid(),getppid());
	if(getpid() == second_pid) printf("2 pid=%d, 2 ppid=%d\n",getpid(),getppid());
	if(getpid() == third_pid) printf("3 pid=%d, 3 ppid=%d\n",getpid(),getppid());
	if(getpid() == fourth_pid) printf("4 pid=%d, 4 ppid=%d\n",getpid(),getppid());
	if(getpid() == fifth_pid) printf("5 pid=%d, 5 ppid=%d\n",getpid(),getppid());
	if(getpid() == sixth_pid) printf("6 pid=%d, 6 ppid=%d\n",getpid(),getppid());

	return 0;
}