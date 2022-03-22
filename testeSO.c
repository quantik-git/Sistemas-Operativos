#define LIMITE 10
#define LINHA 10

void send_email(char *arg_list[]) {
	if (fork() == 0) {
		execvp("mail", arg_list);
		perror("erro exec");
		_exit(EXIT_FAILURE);
	}
	pause();
}

int main(int argc, char *argv[]) {
	char linha[LINHA + 1];
	int file, status;
	off_t fim;

	if (argc < 2)
		exit(EXIT_FAILURE);

	file = open(argv[1], O_RDONLY);
	if (file == -1)
		exit(EXIT_FAILURE);

	fim = lseek(file, 0, SEEK_END);
	for (int i = 0; i < LIMITE; i++) {
		switch (fork()) {
			case 0:
				for (int j = 0; lseek(file, 0, SEEK_CUR) != fim; j++) {
					char email[24], *aluno;

					lseek(file, (LINHA * j) + i, SEEK_SET);
					read(file, &linha, LINHA);

					aluno = strtok(linha, " ");
					sprintf(email, "%s@alunos.uminho.pt", aluno);

					char *arg_list[] = {"mail", "-s", "Sistemas_Operativos", email, NULL}
					send_email(arg_list);
				}
				_exit(EXIT_SUCCESS);
				break;
			case -1:
				printf("Erro no fork %d", i);
				break;
			default:
				break;
		}
	}

	for (int i = 0; i < LIMITE; i++) {
		wait(&status);
		printf("%d\n", WEXITSTATUS(status));
	}

	return EXIT_SUCCESS;
}
