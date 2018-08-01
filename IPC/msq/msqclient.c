#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdio.h>

#define FPATH "/home/andrew/shutdown"

struct my_message {
	long type;
	char text[30];
};

int main(int argc, char const *argv[])
{
	int   msg_queue_id;
	key_t msg_queue_access;

	msg_queue_access = ftok(FPATH,'A');
	if(msg_queue_access == -1){
		perror("ftok");
	}


	msg_queue_id = msgget(msg_queue_access, 0);
	if(msg_queue_id == -1){
		perror("msgget");
	}


	//К очереди присоединился. Формирую сообщение.
	struct my_message msg;
	msg.type = 2L;
	strcpy(msg.text,"Hil!");
	//Отправляю
	if(msgsnd(msg_queue_id, &msg, sizeof(struct my_message) - sizeof(long), 0) == -1){
		perror("msgsnd");
	}

	return 0;
}