#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NOME_SIZE 100

ssize_t read_segment(int fd, char *line, size_t size, char delimiter);
void insert_update(int db, char *name, char *age);

int main(int argc, char *argv[]) {
	int db, flag = 0;
	ssize_t n_read;
	char nome[NOME_SIZE];

	if (argc < 4)
		exit(EXIT_FAILURE);

	db = open("db.txt", O_CREAT | O_RDWR, 0600);

	switch (argv[1][1]) {
		case 'i':
			insert_update(db, argv[2], argv[3]);
			break;

		default:
			exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}


ssize_t read_segment(int fd, char *line, size_t size, char delimiter) {
	ssize_t n_read, res = 0;
	while ((n_read = read(fd, &line[res], 1)) > 0)
		if (line[res++] == delimiter)
			break;
	return res;
}

void insert_update(int db, char *name, char *age) {
	ssize_t n_read;
	char nome[NOME_SIZE];
	int flag = 0;

	while ((n_read = read_segment(db, nome, NOME_SIZE, ';')) > 0) {
		nome[n_read-1] = '\0';
		if (!strcmp(nome, name)) {
			flag = 1;
			break;
		}
		read_segment(db, nome, NOME_SIZE, '\n');
	}

	if (!flag) {
		write(db, name, strlen(name));
		write(db, ";", 1);
	}

	write(db, age, strlen(age));
	write(db, "\n", 1);
}
