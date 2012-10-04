//A. Shawn Bandy
//August 29th 2012
//CECS 472
//Assignment 2 

#include <stdio.h>
#include <stdlib.h> /* fork */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
int sum;
main () {
  int i;
  pid_t child_pid;
  char iam; int isleep;
  sum = 0;
  child_pid = fork();  /* create a new process */
  if(child_pid >= 0) {
	if(child_pid > 0) {
		iam = 'P';
		isleep = 1;
	} else {
		iam = 'C';
		isleep = 2;		
	}

	for(i=1; i<=10; i++) {
		sum += i;
		printf("%c sum is %d\n",iam,sum);
		fflush(stdout);
		sleep(isleep);
	}

  } else {
		  perror("fork");
  }
  exit(0);
};
