#include <dlfcn.h>
#include <stdio.h>

int	main(int argc, char const *argv[])
{
	void (*handler)(char*) = dlsym(dlopen("./sanplugin.so",RTLD_LAZY),"printf_wrapper");
	handler("functionality");
	return 0;
}

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
