#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int fd_in;
	int fd_out;

	char buf[10];
	int numb;
	int ret;
	
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input> <output>\n",argv[0]);
		exit(-1);
	}
	printf("Input file: %s\n", argv[1]);	
	printf("Output file: %s\n", argv[2]);

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0) {
		fprintf(stderr, "Error opening file for reading.\n");
	}

	fd_out = open(argv[2], O_WRONLY | O_CREAT);
	if (fd_out < 0) {
		fprintf(stderr, "Error opening file for writing.\n");
	}

	numb = read(fd_in, buf, 10);
	while (numb > 0) {
		ret = write(fd_out,buf,numb);
		if (ret != numb) {
			break;
		}

		numb = read(fd_in, buf, 10);
	}	

	close(fd_in);
	close(fd_out);
}
