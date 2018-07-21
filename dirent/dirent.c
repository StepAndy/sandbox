#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int ret;
	char buf[3000];
	DIR* fopened;
	struct dirent * sopened; 

	fopened = opendir("/home/andrew");
	while((sopened = readdir(fopened)) != 0){
		printf("%d %s\n", sopened->d_type, sopened->d_name);	
	}

	closedir(fopened);
	return 0;
}