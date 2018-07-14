#include <stdio.h>

char *functionality = "printf_wrapper - am doing the same";

void printf_wrapper(char *output)
{
	printf("%s\n", output); //*output
}

void scanf_wrapper(char *input)
{
	scanf("%s",input);
}

/*
char *output;
output = "aasda";
*/