#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
	pid_t pai, filho;

	filho = getpid();
	pai = getppid();

	printf("pai: %d\nfilho: %d\n", pai, filho);
	return 0;
}
