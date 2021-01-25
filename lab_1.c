// Мкртумян Роберт
// БПИ 194
// Лабораторная работа №1
// 25.01.21
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	
	printf("user id = %d\ngroup id = %d", (int)getuid(), (int)getgid());
	return 0;
	
}
