#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1000
#define LINE 8

ssize_t readln(int fd, char *line, size_t size) {
	ssize_t n_read, res = 0;
	while ((n_read = read(fd, &line[res], 1)) > 0)
		if (line[res++] == '\n')
			break;
	return res;
}

int main(int argc, char *argv[]) {
	int source;
	char buffer[BUFFER_SIZE+1], line_num[LINE+1];
	ssize_t n_read;

	if (argc < 2)
		exit(EXIT_FAILURE);

	source = open(argv[1], O_RDONLY);
	if (source == -1)
		exit(EXIT_FAILURE);

	for (int i = 1; (n_read = readln(source, buffer, BUFFER_SIZE)) > 0; i++) {
		sprintf(line_num, "%*d  ", LINE-2, i);
		write(STDOUT_FILENO, line_num, LINE);
		write(STDOUT_FILENO, buffer, n_read);
	}

	if (close(source) == -1)
		exit(EXIT_FAILURE);

	return EXIT_SUCCESS;
}
