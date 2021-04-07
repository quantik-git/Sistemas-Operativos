#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1

/*
Buffers maiores vão fazer com que o output tenha lixo do buffer
O único closed é o destino para detetar erros de escrita. A source é closed automaticamente quando a
funcao exit() é a chamada.
*/
int main(int argc, char *argv[]) {
	int source, destination;
	char buffer[BUFFER_SIZE];
	ssize_t n_read;

	if (argc != 3)
		exit(EXIT_FAILURE);

	source = open(argv[1], O_RDONLY);
	if (source == -1)
		exit(EXIT_FAILURE);

	destination = open(argv[2], O_CREAT | O_RDWR, 0600);
	if (destination == -1)
		exit(EXIT_FAILURE);


	while ((n_read = read(source, buffer, BUFFER_SIZE)) != 0)
		write(destination, buffer, n_read);

	if (close(destination) == -1)
		exit(EXIT_FAILURE);

	return EXIT_SUCCESS;
}
