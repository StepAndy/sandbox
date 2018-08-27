#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>


#define FPATH "/home/andrew/chat.txt"
#define SERVICE_PORT 100
#define ASSIGNMENT_PORT 150
#define COMMON_ROOM 200

struct client_info{
	long type;
	char nickname[25];
} my_info;

struct client_dispatcher{
	long type; 
	long dispatch_port;
} get_my;

struct client_text_msg{
	long type;
	long senders_port;
	char nickname[25];
	char text[255];
} message;

int main(int argc, char const *argv[])
{
	int chat_id;
	key_t chat_key;

	printf("Введите свой ник\n");
	scanf("%s", my_info.nickname);
	my_info.type = SERVICE_PORT;

	chat_key = ftok(FPATH,'A');
	chat_id = msgget(chat_key, 0);

	//Отправляем информацию о себе, чтобы сервер вывел мой ник
	//+ чтобы "явно" присоединиться к чату 
	msgsnd(chat_id, &my_info, sizeof(my_info) - sizeof(long), 0);
	
	//Получить свой отедльный адрес, куда будут копироваться сообщения чата
	// и откуда буду забирать на чтение
	msgrcv(chat_id, &get_my, sizeof(get_my) - sizeof(long),
		ASSIGNMENT_PORT, 0); //Получить ответ с новым типом					
	
	while(1){	
		//Забрать все сообщения, что появились в чате за последнее время 
		//в моем "ящике"
		while(msgrcv(chat_id, &message, sizeof(message) - sizeof(long),
			get_my.dispatch_port, IPC_NOWAIT) > 0){
			//Если сообщение было моим - не печатать его повторно. Иначе печатать
			//if(message.senders_port == get_my.dispatch_port) continue;?
			printf("[%s]\n", message.text);
		}
		scanf("%s", message.text);
		if(strcmp(message.text, "print") == 0) continue; //Пропустить ввод
		message.type = COMMON_ROOM;
		message.senders_port = get_my.dispatch_port;
		strcpy(message.nickname, my_info.nickname);
		msgsnd(chat_id, &message, sizeof(message) - sizeof(long), 0);
	}

	//Теперь можно слать в чат по новому личному порту, откуда будет ...нет
	//Теперь слать в чат общий, откуда будет забираться последовательно сервером и дублироваться всем, а все будут забирать уже 
	//по своим портам в msgrcv 

	return 0;
}

//42.printf("new type = %ld\n", get_my.dispatch_port );

//Если сообщение было моим - не печатать его повторно. Иначе печатать
			//if(message.senders_port == get_my.dispatch_port) continue;?
			//59 printf("[%s sp%ld mp%ld ]\n", message.text, message.senders_port, get_my.dispatch_port);
