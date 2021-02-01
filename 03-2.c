#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

	int pid = (int)fork();
	
	if (pid == -1){
		printf("Не удалось создать новый процесс!\n");
	} else if (pid == 0) {
		printf("Ребенок: PID = %d, PPID = %d\n", (int)getpid(), (int)getppid());
	} else {
		printf("Родитель: PID = %d, PPID = %d\n", (int)getpid(),(int)getppid());
	} 

	return 0;

}
