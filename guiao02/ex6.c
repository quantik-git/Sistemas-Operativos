#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 100

int main(int argc, char *argv[]) {
	int n_col, n_lin, n, res = 0;
	srand(time(NULL));

	if (argc < 4)
		exit(EXIT_FAILURE);

	n_col = atoi(argv[1]);
	n_lin = atoi(argv[2]);
	n = atoi(argv[3]);
	int matrix[n_lin][n_col];

	for (int i = 0; i < n_lin; i++)
		for (int j = 0; j < n_col; j++)
			matrix[i][j] = rand() % MAX_NUM;

	for (int i = 0; i < n_lin; i++) {
		if (fork() == 0) {
			int occ = 0;
			for(int j = 0; j < n_col; j++)
				if (matrix[i][j] == n)
					occ++;
			_exit(occ);
		}
		int occ;
		wait(&occ);
		res += WEXITSTATUS(occ);
	}

	printf("Encontradas %d ocorrências do número %d\n", res, n);

	return 0;
}
