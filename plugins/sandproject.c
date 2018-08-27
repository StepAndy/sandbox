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
