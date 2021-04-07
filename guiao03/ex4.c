#include <unistd.h>

int main(int argc, char *argv[]) {
	int exec_ret;
	exec_ret = execv("./ex3", argv);

	return exec_ret;
}
