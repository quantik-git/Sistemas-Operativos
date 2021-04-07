#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1

int main(int argc, char *argv[]) {
	int source, destination = STDIN_FILENO;
	char buffer[BUFFER_SIZE];
	ssize_t n_read;

	if (argc < 2)
		exit(EXIT_FAILURE);

	for (int i = 1; i < argc; i++) {
		source = open(argv[1], O_RDONLY);
		if (source == -1)
			exit(EXIT_FAILURE);

		while((n_read = read(source, buffer, BUFFER_SIZE)) != 0)
			write(destination, buffer, n_read);

		if (close(source) == -1)
			exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
