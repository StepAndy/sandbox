#include <unistd.h>
#include <stdio.h>

int	main()
{
	pid_t returned_forks_result; //Создаем переменную.
	
	printf("pid = %d\n", getpid()); //Выводим айди родительского процесса

	returned_forks_result = fork(); // с этого момента программа разветвляется,
	// появляется дочерний процесс, а процесс вызвавший fork становится род-ем.
	// В переменную pid возвращаются разные значения для родителя и потомка.
	
	//Но результат, вернувшийся после вызова fork и pid процесса - разные вещи
	if (returned_forks_result == 0) 
		printf("I'm child with pid = %d, ppid = %d \
		[Fork returned = %d]\n", getpid(), getppid(), returned_forks_result);
	else printf("I'm parent with pid = %d, ppid = %d \
		[Fork returned = %d]\n", getpid(), getppid(), returned_forks_result);
	return 0;

	//В результате выполнения программы можно заметить, что:
	//родителю fork вернул значение, равное pid дочернего процесса
	//дочернему процессу fork вернул значение равное 0  
}