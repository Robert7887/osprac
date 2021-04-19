#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>

// Принцип работы программы:
// Работает по классическому алгоритму писатель-читатель.
// Начальное значение семафора равно нулю.
// Первым право записи в pipe получает родитель, т.к.
// ребенок изначально пытается отнять 1 от уже нулевого счетчика.
// Далее после записи в pipe родителский процесс увеличивает счетчик семафора,
// тем самым отдавая права записи-чтения в pipe дочернему процессу.
// Тот в свою очередь читает переданное родительским процессом сообщение,
// записывает свое сообщение в pipe и отдает право родителю.
// И так N итераций.
int main() {

	int fd[2], res;
	size_t size = 0;
	key_t key;
	char pathname[] = "05-3.c";
	struct sembuf mybuf;
	char resString[18];
	int semid;

	int N;
	printf("Enter N: ");
	scanf("%d", &N);
	printf("\n");

  	if ((key = ftok(pathname, 0)) < 0) {
   		printf("can\'t create key\n");
    		exit(-1);
  	}
	
	//create pipe
	if (pipe(fd) < 0) {
		printf("can\'t open pipe\n");
		exit(-1);
	}
	
	if ((semid = semget(key, 1, 0666)) < 0) {
		if((semid = semget(key, 1, 0666 | IPC_CREAT) < 0)) {
			printf("can\'t create semaphore set\n");
			exit(-1);
		}
	}


	if ((res = fork()) < 0) {
		printf("can\'t fork child\n");
		exit(-1);
	} else if (res > 0) {
		// Родительский процесс
		for (size_t i = 0; i < N; ++i) {
			if (write(fd[1], "Hello from parent", 18) != 18) {
				printf("Parent process: write error!");
				exit(-1);
			}
			
			// Ждем, когда ребенок отдаст право на чтение
			mybuf.sem_num = 0;
   		 	mybuf.sem_op  = -1;
    			mybuf.sem_flg = 0;
    			semop(semid, &mybuf, 1);

			if ((size = read(fd[0], resString, 18) != 18)) {
				printf("Parent process: read error!\n");
				exit(-1);
			}

			printf("Parent: resString: %s\n", resString);
		}

		close(fd[0]);
	} else {
		// Процесс-ребенок
		for (int i = 0; i < N; ++i) {
			// Ждем пока родитель откроет право на чтение
			if ((size = read(fd[0], resString, 18)) < 0) {
				close(fd[1]);
				close(fd[0]);
				printf("Program finished...\n");
				return 0;
			}
			printf("Child: resString: %s\n", resString);
			if (write(fd[1], "Hello from child!", 18) != 18) {
				printf("Child: write error\n");
				exit(-1);
			}

			// Открываем родителю право на чтение и запись
			mybuf.sem_num = 0;
    			mybuf.sem_op  = 1;
    			mybuf.sem_flg = 0;
    			semop(semid, &mybuf, 1);
		}
	}
}
