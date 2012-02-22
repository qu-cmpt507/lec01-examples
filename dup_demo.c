#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;

	fd = open("outfile", O_WRONLY|O_CREAT);
	if (fd < 0) {
		fprintf(stderr, "Couldn't open file for writing.\n");
	}

	printf("Hi there, this is my program!\n");
	printf("printf() prints to stdout (fd = 1) by default.\n");
	printf("This program shows that...\n");

	dup2(fd, 1);

	printf("This should print into the file\n");
	printf("because fd=1 now points to a file, not stdout.\n");

	close(fd);
	return 0;
}
