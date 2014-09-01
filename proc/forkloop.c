#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  int i;
  int pid;
  int num_children;

  if(argc != 2) {
    fprintf(stderr, "Usage: forkloop <num_children>\n");
    exit(1);
  }

  num_children = atoi(argv[1]);
  printf("Main process: %d\n",getpid());

  for(i = 0; i < num_children; i++) {
    pid = fork();
    if(pid < 0) {
      perror("fork failed");
      _exit(2);
    } else if(pid == 0) {
      printf("New Child: %d, parent: %d, i = %d\n", getpid(), getppid(),i);
    } 
  }

  sleep(5);
  return 0;
}
