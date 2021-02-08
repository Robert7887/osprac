#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[]) {

	int pid = (int)fork();
	
	if (pid == -1) {
		printf("Не удалось создать новый процесс!\n");
	} else if (pid == 0) {
		(void)execle("/bin/cat", "/bin/cat", "03-4.c", 0, envp);
	} else {
		// Ветка родительского процесса.
	} 

	return 0;

}
