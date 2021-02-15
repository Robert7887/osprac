#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int     parentPipe[2], childPipe[2], result;

  size_t size;
  char  resstring[14];

  if (pipe(parentPipe) < 0) {
    printf("Can\'t open parent pipe\n");
    exit(-1);
  }

  if (pipe(childPipe) < 0) {
    printf("Can\'t open child pipe\n");
    exit(-1);
  }

  result = fork();

  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (result > 0) {

   /* Parent process */

    if (close(parentPipe[0]) < 0) {
      printf("parent: Can\'t close reading side of parent pipe\n"); exit(-1);
    }

    size = write(parentPipe[1], "Hello, world!", 14);

    if (size != 14) {
      printf("Can\'t write all string to parent pipe\n");
      exit(-1);
    }

    if (close(parentPipe[1]) < 0) {
      printf("parent: Can\'t close writing side of parent pipe\n"); exit(-1);
    }

    printf("Parent finished writing\n");

    if (close(childPipe[1]) < 0) {
      printf("parent: Can\'t close writing side of child pipe\n"); exit(-1);
    }

    size = read(childPipe[0], resstring, 14);

    if (size < 0) {
      printf("Can\'t read string from child pipe\n");
      exit(-1);
    }

    printf("Parent finished reading\n");
    printf("parent: resstring = %s\n", resstring);

    if (close(childPipe[0]) < 0) {
      printf("parent: Can\'t close reading side of child pipe\n"); exit(-1);
    }

    printf("Parent exit\n");

  } else {

    /* Child process */

    if (close(parentPipe[1]) < 0) {
      printf("child: Can\'t close writing side of parent pipe\n"); exit(-1);
    }

    size = read(parentPipe[0], resstring, 14);

    if (size < 0) {
      printf("Can\'t read string from parent pipe\n");
      exit(-1);
    }

    if (close(parentPipe[0]) < 0) {
      printf("child: Can\'t close reading side of parent pipe\n"); exit(-1);
    }

    printf("Child finished reading\n");
    printf("child: resstring = %s\n", resstring);

    if (close(childPipe[0]) < 0) {
      printf("child: Can\'t close reading side of child pipe\n"); exit(-1);
    }

    size = write(childPipe[1], "Hello, world!", 14);

    if (size != 14) {
      printf("Can\'t write all string to child pipe\n");
      exit(-1);
    }

    if (close(childPipe[1]) < 0) {
      printf("child: Can\'t close writing side of child pipe\n"); exit(-1);
    }

    printf("Child finished writing\n");
    printf("Child exit\n");
  }

  return 0;
}
