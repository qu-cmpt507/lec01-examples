#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	pid_t npid;
	int status;
	char *args[3];

	printf("Hello.  This program will fork a new process\n");
	printf("to call ls.  Then it will wait for that process\n");
	printf("to terminate.\n");

	pid=fork();
	if (pid == 0) {
		/* Child */
		
		args[0] = "ls";
		args[1] = "-la";
		args[2] = NULL;

		execvp("ls",args);
	}
	else {
		/* Parent */
		npid = wait(&status);
		printf("Done waiting. pid=%d npid=%d\n", pid, npid);
	}

}
