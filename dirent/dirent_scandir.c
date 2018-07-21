#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int contents;
	char buf[3000];
	DIR* fopened;
	const char *dirp;
	struct dirent **sopened; 

	dirp = "/home/andrew";

	fopened = opendir(dirp);
	contents = scandir(dirp, &sopened, NULL, alphasort);

	int i = 0;
	while(contents--){
		printf("%d %s\n", sopened[i]->d_type, sopened[i]->d_name);
		i++;	
	}

	closedir(fopened);
	return 0;
}