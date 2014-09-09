// shmem_client.c -- shared memory client
// incomplete!
// 2014-09-08 Ulrich Baum
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//TODO: some header files

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
  //TODO

  // open shared memory segment - must be created by server
  //TODO

  // attach shared memory segment to local address space
  //TODO

  // set pointer variabes to access shared data
  //TODO

  current = 0;  // current version of data received, initially 0
  // main loop - read and print new data
  while(1) {
    // wait for new data
    while (*version == current);
    current = *version;
    // read and print string from shared segment
    strcpy(buf, data);
    printf("%s\n", buf);
  }
}
