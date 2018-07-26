#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>	

#define CNSMRS_NUM 3

int shop_department[5];
int global_index = 0;
pthread_mutex_t 
	mutex_index = PTHREAD_MUTEX_INITIALIZER; //для индексации покупателя
pthread_mutex_t mutex_department[5] = {
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER
};


//long indexed_consummer[CNSMRS_NUM];
void *loader_func(void *arg)
{
	int random_shop;
	while(1){
		random_shop = rand() % ((5 + 1) - 1) + 1;
		for(int i = 0; i < 5; i++){
			if(random_shop == i+1 && pthread_mutex_trylock(&mutex_department[i]) == 0){
				shop_department[i] += 500;
				sleep(2);
				printf("%d\n", shop_department[i]);
				pthread_mutex_unlock(&mutex_department[i]);
			}
		}
	}
}

void *cnsmrs_func(void *arg)
{	
	pthread_mutex_lock(&mutex_index);
	int random_shop, demand;
	int local_index;
	global_index++;
	local_index = global_index;
	demand = rand() % ((11000 + 1) - 9000) + 9000;
	pthread_mutex_unlock(&mutex_index);
	
	while(demand > 0){
		random_shop = rand() % ((5 + 1) - 1) + 1;
		for(int i = 0; i < 5; i++){
			if(random_shop == i+1 && pthread_mutex_trylock(&mutex_department[i]) == 0){
				demand -= shop_department[i];
				shop_department[i] = 0;
				sleep(1);
				printf("index [%d],demand [%d]\n", local_index, demand);
				pthread_mutex_unlock(&mutex_department[i]);
			}
		}		
	}


	
}

int main(int argc, char const *argv[])
{	
	pthread_t the_loader;
	pthread_t consumer[3];

	//Задал рандомное количество товаров в каждом отделе 
	for(int i = 0; i < 5; i++){
		shop_department[i] = rand() % ((1100 + 1) - 900) + 900;
	}

	if(pthread_create(&the_loader, NULL, loader_func, NULL)){
		perror("pthread_create");
	}

	for(int i = 0; i < 3; i++){
			if(pthread_create(&consumer[i], NULL, cnsmrs_func, NULL)){
			perror("pthread_create");
		}
	}
	//pthread_create(&consumer)
	for(int i = 0; i < 3; i++){
			pthread_join(consumer[i], NULL);
	}

	pthread_cancel(the_loader);
	exit(0);
	return 0;
}

/*
	//Если это не бред, то придется залочить и разлочить
	while(1){
		if(indexed_consummer[0] == 0){
			indexed_consummer[0] = pthread_self();	
			break;
		} 
		if(indexed_consummer[1] == 1){
			indexed_consummer[1] = pthread_self();
			break;
		} 
		if(indexed_consummer[2] == 2){
			indexed_consummer[2] = pthread_self();
			break;	
		} 
	}
*/