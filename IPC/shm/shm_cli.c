#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
struct memory_chunk {
	char all[7000];
	char latest[150];
	int mark;
};

int main(int argc, char const *argv[])
{
	key_t key;
	int id, mark;
	struct memory_chunk *chat;
	key = ftok("Makefile",'A');
	id = shmget(key, sizeof(chat), IPC_CREAT | 0644);
	chat = (struct memory_chunk*)shmat(id, 0, 0);
	mark = chat;
	while(1){
		printf("%s\n", chat->all);
		chat->mark = mark;
		scanf("%s", chat->latest);
		if(chat->mark != mark){
			printf("%s\n", chat->latest);
		}
	}
	return 0;
}

//Логика нарушена - нет семафоров в цикле после 20 строки