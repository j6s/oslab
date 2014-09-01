#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int i;
  for (i=0; i<10;i++) {
    if (fork() == 0) {
       printf("child %d started\n",i);
       sleep(10);
       printf("child %d exiting\n",i);
       exit(0);
    }
  }

  /* add wait instructions here to avoid zombies */
  sleep(30);
  exit(0);
}
