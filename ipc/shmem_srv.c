// shmem_server.c -- shared memory server example
// incomplete!
// 2014-09-08 Ulrich Baum
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//TODO some header files

#define SHMEMSIZE 256

int main(int argc, char *argv[]) {

  key_t key;    // key for shared memory segment
  int id;       // shared memory segment id
  char *shared; // pointer to shared memory segment in our address space
  char *data;   // data sent/received
  char *version;  // data version in shared memory
  char current;   // local data version
  char buf[SHMEMSIZE-1]; // data buffer

  // need exactly one command line argument
  if (argc != 2) {
    fprintf(stderr,"usage: %s key\n", *argv);
    exit(1);
  }
  
  // get shared memory key from command line
  // TODO

  // open shared memory segment, create if it doesn't exist
  // TODO

  // attach shared memory segment to local address space
  // TODO

  // set pointer variabes to access shared data
  // TODO
  

  current = 0;  // current version of data received, initially 0
  // main loop - read and send new data
  do {
    scanf("%s", buf);  // read new string from console
    strcpy(data, buf); // copy to shared memory segment
    *version = ++current;       // update counter to notify clients
  } while (strcmp(buf, "QUIT") != 0);


  exit(0);  // this automatically detaches the segment

}
