// demo program for linux signals
// 2014-09-08 Ulrich Buam

#include <stdio.h>
#include <signal.h>

void myhandler (int sig) {
  printf("Received signal %d, but I don't care!\n", sig);
}

int main() {
  signal(SIGTSTP, SIG_IGN);
  signal(SIGINT, myhandler);
  while(1);
}
