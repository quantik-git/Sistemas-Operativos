#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>

int main() {
	pid_t pid;
	int status;

	for (int i = 1; i < 11; i++) {
		if ((pid = fork()) == 0) {
			printf("Self: %d\nPai: %d\n", getpid(), getppid());
			_exit(i);
		}
	}

	for (int i = 0; i < 10; i++) {
		pid = wait(&status);
		printf("Pid %d\tStatus %d\n", pid, WEXITSTATUS(status));
	}

	return 0;
}
