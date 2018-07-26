#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int ind = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void *func()
{	
	pthread_mutex_lock(&mut);
	/*int tmp = ind;
	tmp++;
	ind = tmp;*/
	ind++;
	printf("I was called %d, My tid is %ld \n", ind, pthread_self());
	pthread_mutex_unlock(&mut);
} 

int main(int argc, char const *argv[])
{
	pthread_t thread_num[5];
	int i;
	for(i = 0; i < 5; i++){
		pthread_create(&thread_num[i], NULL, func, NULL);
	}
	for(i = 0; i < 5; i++){
		pthread_join(thread_num[i], NULL);
	}
	return 0;
}