#include <unistd.h>
#include <stdio.h>

int main() {
	execlp("ls", "ls", "-l", NULL);

	printf("Nunca vai chegar aqui\n");

	return 0;
}
