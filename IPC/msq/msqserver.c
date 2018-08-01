#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>

#define FPATH "/home/andrew/shutdown"

struct my_message {
	long type;
	char text[30];
} msg;

int main(int argc, char const *argv[])
{
	int   msg_queue_id;
	key_t msg_queue_access;

	msg_queue_access = ftok(FPATH,'A');
	if(msg_queue_access == -1){
		perror("ftok");
	}
	

	msg_queue_id = msgget(msg_queue_access, IPC_CREAT | 0666);
	if(msg_queue_id == -1){
		perror("msgget");
	}


	if(msgrcv(msg_queue_id, &msg, sizeof(struct my_message) - sizeof(long), 2L, 0) == -1){
		perror("msgrcv");
	} 


	printf("%s\n", msg.text);
	msgctl(msg_queue_id, IPC_RMID, 0); 
	return 0;
}


//malloc text