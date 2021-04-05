#include <pthread.h>

#include <stdio.h>

#include <stdlib.h>

int a = 0;

void *mythread(void *dummy) {

  pthread_t mythid;

  mythid = pthread_self();

  a = a+1;

  printf("First new thread %u, Calculation result = %d\n", mythid, a);

  return NULL;

}

void *mythread2(void *dummy) {

  pthread_t mythid;

  mythid = pthread_self();

  a = a*10;

  printf("Second new thread %u, Calculation result = %d\n", mythid, a);

  return NULL;

}

/**

  The main() function is also an associated function of the main thread.

**/

int main() {

  pthread_t thid, mythid, thid2, mythid2;

  int result;

  result = pthread_create (&thid, (pthread_attr_t *)NULL, mythread, NULL);

  if (result != 0) {

    printf ("Error on first thread create, return value = %d\n", result);

    exit(-1);

  }

  printf("First new thread created, thid = %u\n", thid);


  result = pthread_create (&thid2, (pthread_attr_t *)NULL, mythread2, NULL);

  if (result != 0) {

    printf ("Error on second thread create, return value = %d\n", result);

    exit(-1);

  }

  printf("Second new thread created, thid = %u\n", thid2);


  mythid = pthread_self();

  a = a+5;

  printf("Main Thread %u, Calculation result = %d\n", mythid, a);

  pthread_join(thid, (void **)NULL);
  pthread_join(thid2, (void **)NULL);

  return 0;

}

