#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

  int ret;

  printf("parent started\n");
  ret = fork();
  printf("forked\n");

  if(ret < 0) {
    perror("fork failed");
    _exit(2);
  } else if(ret == 0) {
    // fork returned zero, we're in the child
    printf("Child: %d with parent: %d\n", getpid(), getppid());
  } else {
    // positive return value of fork is the child's pid
    printf("Parent: %d created child with pid %d\n", getpid(),ret);
  }

  printf("hello\n");
  sleep(1);
  return 0; // ok
}

