#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1

ssize_t readln(int fd, char *line, size_t size) {
	ssize_t res = 0;
	ssize_t i = 0;

	while ((res = read(fd, &line[i], size)) != 0 && ((char) line[i-1] != '\n'))
		i += res;

	return i;
}

int main(int argc, char *argv[]) {
	char line[100];
	ssize_t size;

	if (argc != 3)
		exit(EXIT_FAILURE);

	int fd = open(argv[1], O_RDONLY);
	ssize_t tam = (ssize_t) atoi(argv[2]);

	size = readln(fd, line, tam);
	write(STDIN_FILENO, &line, size);
	close(fd);

	return EXIT_SUCCESS;
}
