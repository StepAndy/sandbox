#include <dlfcn.h>
#include <stdio.h>

int	main(int argc, char const *argv[])
{
	int (*summ)(int a, int b);
	int (*diff)(int a, int b);
	
	void *lib;
	char *text;
	lib = dlopen("/home/andrew/Рабочий стол/sandbox/plugins/sandplugin.so", RTLD_LAZY);
	text = dlsym(lib,"functionality");

	printf("%s\n", text);
	dlclose(lib);
	return 0;
}

/*  int a = 5;
	int b = 6;
	int summm = summ(a,b);*/
/*

int	main(int argc, char const *argv[])
{
	int libfd = dlopen("./sanplugin.so",RTLD_LAZY); //Почему ворнинги на дексриптор? 
	char *functionality = dlsym(libfd,"functionality");
	printf("%s",functionality);
	return 0;
}
*/

/*
int	main(int argc, char const *argv[])
{
	void (*handler)(char*) = dlsym(dlopen("./sanplugin.so",RTLD_LAZY),"printf_wrapper");
	handler("functionality");
	return 0; //Ошибка сегментирования (стек памяти сброшен на диск
}

*/
