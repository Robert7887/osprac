#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {

    printf("Количество аргументов командной строки: %d\n", argc);

    printf("Аргументы командной строки: \n");
    for (int i = 0; i < argc; i++) {
	printf("[%d]: %s\n", i, argv[i]);
    }
    
    printf("\nПараметры окружающей среды:\n");
    int i = 0;
    while (envp[i] != NULL) {
        printf("[%d]: %s\n", i, envp[i]);
	i++;
    }

    printf("\n");

    return 0;

}
