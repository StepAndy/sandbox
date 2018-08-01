#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define FPATH "/home/andrew/chat.txt"
#define SERVICE_PORT 100
#define ASSIGNMENT_PORT 150
#define COMMON_ROOM 200

int GLOBAL_ID;

struct client_info{
	long type;
	char nickname[25];
} connected;


struct client_dispatcher{
	long type;
	long dispatch_port;
} assign;


struct dispatch_messages{
	long type;
	long from_port;
	char nickname[25];
	char text[255];
} dispatch;


void sig_int(int errno)
{
	msgctl(GLOBAL_ID, IPC_RMID, 0);
	printf("deleted queue");
	sleep(1);
	exit(0);
}


int main(int argc, char const *argv[])
{
	int 	chat_id;
	key_t 	chat_key;
	long 	new_dispatch_port = 0;

	chat_key = ftok(FPATH,'A');
	chat_id = msgget(chat_key, IPC_CREAT | 0666);

	GLOBAL_ID = chat_id;

	signal(SIGINT, sig_int);

	while(1){
		//Если кто-то отправил сообщение о подключении - назначить ему личный адрес куда посылать копии общего чата 
		if(msgrcv(chat_id, &connected, sizeof(connected) - sizeof(long), 
			SERVICE_PORT, IPC_NOWAIT) > 0){
			assign.type = ASSIGNMENT_PORT;
			assign.dispatch_port = ++new_dispatch_port;
			msgsnd(chat_id, &assign, sizeof(assign) - sizeof(long), IPC_NOWAIT); 	
			//Рассылаю всем сообщение, что подключился новый участник 
			strcpy(dispatch.text,connected.nickname);
			strcat(dispatch.text," connected");
			printf("new dispatch port = %ld\n", new_dispatch_port);
			for(long port_num = 1; port_num <= new_dispatch_port; port_num++){
				dispatch.type = port_num;
				if(port_num == dispatch.from_port) continue;
				msgsnd(chat_id, &dispatch, sizeof(dispatch) - sizeof(long), IPC_NOWAIT);
				printf("[%s connected]\n", connected.nickname);
			}
			
		}
		if(msgrcv(chat_id, &dispatch, sizeof(dispatch) - sizeof(long), 
			COMMON_ROOM, IPC_NOWAIT) > 0){
			char text[255]="";
			strcpy(text, dispatch.nickname);
			strcat(text, ":");
			strcat(text, dispatch.text);
			strcpy(dispatch.text, text);
			for(long port_num = 1; port_num <= new_dispatch_port; port_num++){
				dispatch.type = port_num;
				if(port_num == dispatch.from_port) continue;
				msgsnd(chat_id, &dispatch, sizeof(dispatch) - sizeof(long), 0);
			}
		}
	}	
 
 	//75 printf("[%s connected]\n", connected.nickname);
	//printf("[%s connected]\n", their.nickname); //не printf, a msgsnd всем

	//msgsnd(chat_id, &assign, sizeof(assign) - sizeof(long), 0);

	msgctl(chat_id, IPC_RMID, 0);
	return 0;
}