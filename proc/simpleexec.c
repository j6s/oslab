#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]){

  // build argument list, this will run: ls  -l /bin 
  char * ls_args[4] = { "ls", "-l", "/bin", NULL} ;

  execv( "/bin/ls", ls_args);

  // we only get here if exec failed 
  perror("exec failed");
  return 2; //return error code 
}
