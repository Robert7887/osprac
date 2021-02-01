#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

	printf("PID = %d\nPPID = %d", (int)getpid(), (int)getppid());
	return 0;

}
