// test scheduler
#include "types.h"
#include "user.h"

#define DELAY (1<<21)

void run(char *name, int duration) {

  int i, j;

  for (i = 0; i < duration; i++) {
    printf(1,name);
    for (j=0; j < DELAY; j++); 
  }
}


void forkrun(char *name, int duration, int prio) {
  if (fork() == 0) {
    setpriority(prio);
    printf(1,"\n+++ starting: %s prio: %d\n",name, prio);
    run(name, duration);
    printf(1,"\n--- done:     %s\n",name);
    exit();
  }
  // do nothing in parent
}

int main (int argc, char *argv[])
{
  // run different processes with different priorities
  printf(1, "\n*** Test 1: equal priorities ***"); 
  forkrun("A", 10, 50);
  forkrun("B", 10, 50);
  forkrun("C", 10, 50);
  forkrun("D", 10, 50);
  // wait for all children to terminate 
  while (wait() != -1);

  printf(1, "\n*** Test 2: different priorities ***"); 
  forkrun("A", 10, 50);
  forkrun("B", 10, 51);
  forkrun("C", 10, 52);
  forkrun("D", 10, 53);
  // wait for all children to terminate 
  while (wait() != -1);

  printf(1, "\n*** Test 3: 2 priority groups ***"); 
  forkrun("A", 10, 60);
  forkrun("B", 10, 60);
  forkrun("C", 10, 60);
  forkrun("D", 10, 50);
  forkrun("E", 10, 50);
  forkrun("F", 10, 50);
  // wait for all children to terminate 
  while (wait() != -1);

  exit();
}
