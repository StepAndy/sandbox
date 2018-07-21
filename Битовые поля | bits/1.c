#include <stdio.h>

struct bytes
{
	unsigned int b1:1;
	unsigned int b2:1;
	unsigned int b3:1;
	unsigned int b4:1;
	unsigned int b5:1;
	unsigned int b6:1;
	unsigned int b7:1;
	unsigned int b8:1;
};

int main(int argc, char const *argv[])
{
	int number = 8;
	struct bytes *Bytes;
	Bytes = &number;
	printf("%d %d %d %d %d %d %d %d \n", (*Bytes).b8, (*Bytes).b7, (*Bytes).b6, 
		(*Bytes).b5, (*Bytes).b4, (*Bytes).b3, (*Bytes).b2, (*Bytes).b1 );
	return 0;
}