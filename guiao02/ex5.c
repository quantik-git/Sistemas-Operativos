#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>

int main() {
	pid_t pid;
	int status, i;

	for (i = 1; i < 11; i++) {
		printf("Self: %d\tPai: %d\tI: %d\n", getpid(), getppid(), i);
		if (fork()) {
			pid = wait(&status);
			printf("PID: %d\tStatus: %d\tI: %d\n", pid, WEXITSTATUS(status), i);
			_exit(i);
		}
	}

	return 0;
}
