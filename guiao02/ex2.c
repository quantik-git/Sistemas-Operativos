#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
	pid_t filho;
	int status;

	if (fork() == 0) {
		printf("\tpai: %d\n\tself: %d\n", getppid(), getpid());
		_exit(0);
	} else {
		filho = wait(&status);
		printf("terminal: %d\nself: %d\nfilho: %d\n", getppid(), getpid(), filho);
	}

	return 0;
}
