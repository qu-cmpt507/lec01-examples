#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	pid_t pid;
	pid_t npid;
	int status;
	int filedes[2];
	char buf[10];
	int numb;
	char cmsg[] = "From child: ";
	char msg[] = "Here is some sample text to send.\n";

	/* Create a pipe */
	pipe(filedes);

	pid=fork();
	if (pid == 0) {
		/* Child */

		/* Close the write descriptor, we only read */
		close(filedes[1]);

		write(1, "From child: ", 12);
		while((numb=read(filedes[0], buf, 10))) {
			write(1, buf, numb);
		}

		close(filedes[0]);
		exit(0);
	}
	else {
		/* Parent */

		/* Close the read descriptor, we don't need it. */
		close(filedes[0]);

		write(filedes[1], msg, strlen(msg));

		close(filedes[1]);
		wait(&status);
	}

	return 0;
}
