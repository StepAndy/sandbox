#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

int GLOBAL_ID;

void sig_int(int errno)
{
	shmctl(GLOBAL_ID, IPC_RMID, 0);
}

struct memory_chunk {
	char all[7000];
	char latest[150];
	int mark;
};

int main(int argc, char const *argv[])
{
	key_t key;
	int id;
	struct memory_chunk *chat;
	struct sembuf lock[2] = {0, 0, 0,
							0, 1, 0};
	struct sembuf unlock = {0, -1, 0};
	key = ftok("Makefile",'A');
	id = shmget(key, sizeof(struct memory_chunk), IPC_CREAT | 0644);
	memcpy(&GLOBAL_ID, &id, sizeof(int)); //GLOBAL_ID = id. Just for my pleasure.
	signal(SIGINT, sig_int);
	
	chat = shmat(id, 0, 0);

	shmctl(id, IPC_RMID, 0);
	return 0;
}
