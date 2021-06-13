#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int next_flag = 1;

void handle(int sig) {
	next_flag = 0;
}

int main() {
	pid_t pid, receiver_pid;
	// Пересылаемое значение
	int send_value;

	(void)signal(SIGUSR1, handle);

	// Печатаем наш pid в консоль
	pid = getpid();
	printf("Sender pid = %d\n", pid);

	// Получаем с консоли pid receiver-а
 	printf("Enter pid = ");
 	scanf("%d", &receiver_pid);

	// Получаем с консоли значение для передачи
 	printf("Enter send_value = ");
 	scanf("%d", &send_value);

	// Побайтово передаем значение receiver-у
 	int byte = 1;
 	while (next_flag);
 	while (byte != 0) {
		if ((send_value & byte) == 0) {
			kill(receiver_pid, SIGUSR1);
		} else {
			kill(receiver_pid, SIGUSR2);
    		}
		byte = byte << 1;
		next_flag = 1;
		while(next_flag);
	}
}
