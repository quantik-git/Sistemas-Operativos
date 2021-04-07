#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		if (fork() == 0) {
			execlp(argv[i], "", NULL);
			_exit(i);
		}
	}

	for (int i = 1; i < argc; i++)
		wait(NULL);

	return 0;
}
