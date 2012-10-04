//A. Shawn Bandy
//August 29th 2012
//CECS 472
//Assignment #2

#include <stdio.h>
#include <stdlib.h> /* fork */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
int sum;
main () {
  int i;
  pid_t child_pid;
  sum = 0;
  child_pid = fork();  /* create a new process */
  for (i=1; i<=10; i++) {
    sum += i;
    //printf("sum is %d\n", sum);
    //fflush(stdout);
    if(child_pid == 0) {
	    printf("C sum is %d\n",sum);
	    fflush(stdout);
	    sleep(2);
    } else if(child_pid > 0) {
	    printf("P sum is %d\n",sum);
	    fflush(stdout);
	    sleep(1);
    } else {
	    perror("fork");
	    exit(0);
  }
  }
  exit(0);
};
