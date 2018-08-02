#include <sys/ipc.h>
#include <sys/shm.h>

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
	key = ftok("Makefile",'A');
	id = shmget(key, sizeof(chat), IPC_CREAT | 0644);

	GLOBAL_ID = id;
	signal(SIGINT, sig_int);
	while(1){ }
	return 0;
}