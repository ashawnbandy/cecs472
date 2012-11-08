/* A. Shawn Bandy F1
 * CECS472
 * Assignment 17 - Preallocated Browser Server
 * Assignment 09 - MODIFIED FROM
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
void reaper();

int main(int argc, char *argv[])
{
        struct  sockaddr_in fsin;       /* the from address of a client */
        char    *service = get_port();   /* service name or port number  */
        int     msock, ssock;           /* master & slave sockets       */
        int     alen;                   /* from-address length          */
	int childpid;
	int i;

	signal(SIGPIPE,SIG_IGN);
	signal(SIGCHLD,reaper);
        switch (argc) {
        case    1:
                break;
        case    2:
                service = argv[1];
                break;
        default:
                errexit("<klaxon>\n");
        }

        msock = passiveTCP(service, QLEN);
	
	printf("Server listening on:  %s\n",get_port());
	alen = sizeof(fsin);

		for(i = 0;i <= 1;i++) {
			if(fork() <= 0)
				break;
			printf("Forked a child (%i).\n",getpid());
		}
		printf("(%i)\n",getpid());
		while (  
			((ssock = accept(msock, (struct sockaddr *)&fsin, &alen)) >= 0) 
		      ) 
			{
				printf("(%i) Client connected on ssock %i.\n",getpid(),ssock);
				while(serv(ssock) > 0);
				printf("(%i) Client finished - will close ssock %i",getpid(),ssock);
				close(ssock);
				printf("(%i) ssock %i closed\n",getpid(),ssock);
			}

		/*
		printf("alen: %i\tssock: %i\tchildpid: %i\n",alen,ssock,childpid);
		if(childpid == 0) {
			close(msock);
			while(serv(ssock));
			exit(0);
		} else errexit("<beep>");
		*/
	}

	// This is the service loop (essentially the inside of the while(1)
	int serv(int fd) {
		char * wd;
		char buf[1024] = {};
		int i = 0;
		int n = 0;
		char dir[1022] = {};
		
		do {
			n = recv(fd,&buf[i],sizeof(buf)-i,0);
			printf("Value of n: %i\n",n);
			if(n <= 0) return -1;
			i += n;
			
		} while (i < sizeof(buf) && buf[i-1] != '\0');

		printf("i: %i,n: %i,buf: %s\n",i,n,buf);
		
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
				return -1;
				break;
		}
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
void reaper() {
	int status;
	while(wait3(&status, WNOHANG, NULL > 0));
	(void) signal(SIGCHLD,reaper);
}
