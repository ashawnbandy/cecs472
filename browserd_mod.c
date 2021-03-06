/* A. Shawn Bandy F1
 * CECS472
 * Assigment 9 - Server (corrected)
 * Assignment 14 - MODIFIED
 * 09/21/2012
*/
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "passiveTCP.c"
#include "get_port.c"

#define QLEN    5

int serv(int fd);
void command_list(int fd);
void command_print_cwd(int fd);
void command_change_directory(int fd, char * dir);
void command_get_file(int fd,const char * filename);

// This is the service loop (essentially the inside of the while(1)
int serv(int fd) {
	char buf[1024]={};
	do {
		char * wd;
		int i = 0;
		int n = 0;
		char dir[1022] = {};
		do {
			n = read(fd,&buf[i],sizeof(buf)-i);
			i += n;
		} while (i < sizeof(buf) && buf[i-1] != '\0');
		if(n < 0) errexit("read problem");

//	printf("i: %i,n: %i,buf: %s\n",i,n,buf);
	
		switch(buf[0]) {
			case 'l':
				command_list(fd);
				break;
			case 'p':
				command_print_cwd(fd);
				break;
			case 'c':
				command_change_directory(fd,&buf[2]);
				break;
			case 'g':
				command_get_file(fd,&buf[2]);
				break;
			default:
				buf[0] = '\0';
				break;
		}
	} while (buf[0] != '\0');
	return 1;
}

void command_change_directory(int fd, char * dir) {
	chdir(dir);
}
void command_print_cwd(int fd) {
	char write_buf[64] = {};
	getcwd(write_buf,sizeof(write_buf));
	write(fd,write_buf,sizeof(write_buf));
	write(fd,"\0",1);
}
void command_list(int fd) {
	
	struct stat buf;
	DIR *dirp;
	struct dirent *dp;
	
	char write_buf[1024] = {};
	int n = 0;

	dirp = opendir(".");
	for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {
		stat(dp->d_name, &buf);
		n = sprintf(write_buf, "%s\t%s",dp->d_name, ctime(&(buf.st_mtime)));
		if(n > 0) (void) write(fd,write_buf,n);
	} 
	write(fd,"\0",1);
	closedir(dirp);
	
}
void command_get_file(int fd,const char * filename) {
	struct stat buf;
	int fileSize;
	int src_fd;
	int transferCount;
	char filebuf[256];
	int readSize;
        /* Get the file size */
        stat(filename, &buf);
        fileSize = htonl(buf.st_size);
        /* open the input file */
        src_fd = open(filename,0);
        /* open the destination file */
        // dest_fd = open("xfer.tmp",O_CREAT|O_WRONLY|O_TRUNC,0644);
        /* copy the file using the fileSize */
        transferCount = 0;
	write(fd,(char *)&fileSize,sizeof(fileSize));
        while (transferCount < buf.st_size)
        {
          readSize = read(src_fd, filebuf, sizeof(filebuf));
          write(fd, filebuf, readSize);
          transferCount += readSize;
        }
        close(src_fd);
}
