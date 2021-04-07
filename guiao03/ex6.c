#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MAX_OPTS 10

int my_system(char *command) {
	int exec_ret, status;
	char *exec_args[MAX_OPTS], name;

	exec_args[0] = strtok(command, " ");

	for (int i = 1; i < MAX_OPTS && exec_args[i-1] != NULL; i++)
		exec_args[i] = strtok(NULL, " ");

	exec_args[MAX_OPTS] = NULL;

	switch(fork()) {
		case 0:
			exec_ret = execvp(exec_args[0], exec_args);
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

	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
	int system_ret;

	printf("A executar o comando %s\n", argv[1]);
	system_ret = my_system(argv[1]);

	return system_ret;
}

