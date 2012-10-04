/*
A. Shawn Bandy
CECS472
Assignment 1
08/29/2012
*/

#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
int main (int argc, char* argv[]) {
	int copy_fd;  
	int src_fd;
  char filebuf[256]; /* a small buffer used to copy the file */
  int readSize; // Could also say   size_t readSize

  src_fd = open(argv[1],O_RDONLY);

copy_fd = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
  while (( readSize = read(src_fd, filebuf, sizeof(filebuf)-1)) > 0)
  {
    // I turn it into a string only because I'm using printf;
    // making a copy using "write" would not need this.
    //filebuf[readSize] = '\0';
    //printf("%s",filebuf);
	write(copy_fd,filebuf,readSize);
  }
  close(src_fd);
  return 0;
}
