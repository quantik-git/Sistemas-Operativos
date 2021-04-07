#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int status, exec_ret;

	switch (fork()) {
		case 0:
			exec_ret = execlp("ls", "ls", "-l", NULL);
			_exit(exec_ret);
			break;

		case -1:
			return EXIT_FAILURE;
			break;

		default:
			wait(&status);
			if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
				return EXIT_FAILURE;
	}

	printf("Agora vai chegar aqui\n");

	return 0;
}
