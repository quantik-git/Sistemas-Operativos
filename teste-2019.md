# Teste 2019
## Grupo I
1.

## Grupo II
Versão não concorrente
```c
#define SIZE_ALUNO 6
#define SIZE_LINE 10

void send_email(char line[]) {
	int fd[2];

	pipe(fd);

	char email[] = "a12345@alunos.uminho.pt";
	for (int i = 1; i < SIZE_ALUNO; i++)
		email[i] = line[i];

	if (fork() == 0) {
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execlp("mail", "mail", "-s", "Sistemas_Operativos", email, NULL);
	} else {
		close(fd[0]);
		write(fd[1], line, SIZE_LINE);
		close(fd[1]);
		wait(NULL);
	}
}

int main(int argc, char* argv[]) {
	int lista = open(argv[1], O_RDONLY);
	char line[SIZE_LINE + 1];

	while(read(lista, line, SIZE_LINE) > 0)
		send_email(line);

	return EXIT_SUCCESS;
}
```

## Grupo III
Versão não concorrente
```c
int main(int argc, char* argv[]) {
	char buffer, out[8];
	int counter = 0;
	int fd_in[2], fd_out[2];

	pipe(fd_in);
	pipe(fd_out);

	if (fork() == 0) {
		close(fd_in[1]);
		dup2(fd_in[0], STDIN_FILENO);
		close(fd_in[0]);
		close(fd_out[0]);
		dup2(fd_out[1], STDOUT_FILENO);
		close(fd_out[1]);
		execlp("patgrep", "patgrep", argv[1], NULL);
	} else {
		close(fd_in[0]);
		while (read(STDIN_FILENO, &buffer, 1) > 0)
			write(fd_in[1], &buffer, 1);
		close(fd_in[1]);

		close(fd_out[1]);
		while (read(fd_out[0], &buffer, 1) > 0)
			if (buffer == 'X') counter++;
		close(fd_out[0]);

		sprintf(out, "%d\n", counter);
		write(STDOUT_FILENO, out, sizeof(out));
	}

	return EXIT_SUCCESS;
}
```