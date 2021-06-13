#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int value = 0;
int byte;
pid_t sender_pid;


void zero_handler(int sig) {
	byte <<= 1;
	kill(sender_pid, SIGUSR1);
}

void one_handler(int sig) {
	value |= byte;
	byte <<= 1;
	kill(sender_pid, SIGUSR1);
}

int main() {
	pid_t pid;
	byte = 1;
	
	// Настраиваем handler-ы на прием сигналов
	(void) signal(SIGUSR1, zero_handler);
	(void) signal(SIGUSR2, one_handler);

	// Печатаем наш pid в консоль
	pid = getpid();
	printf("Receiver pid = %d\n", pid);

	// Получаем с консоли pid sender-а
	printf("Sender pid = ");
	scanf("%d", &sender_pid);
	kill(sender_pid, SIGUSR1);

	while (1) {
		if(byte == 0) {
			printf("Received = %d\n", value);
			break;
    		}
  	}
}
