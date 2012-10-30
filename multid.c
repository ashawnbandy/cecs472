/* A. Shawn Bandy F1
 * CECS 472
 * Assignment 14 - Multi-Server
 * 10/15/2012
 */

#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define  UDP_SERV  0
#define  TCP_SERV  1

#define  NOSOCK    -1  /* an invalid socket descriptor  */

struct service {
  char  *sv_name;
  char  sv_useTCP;
  int  sv_sock;
  int  (*sv_func)(int);
};

int  TCPechod(int), TCPchargend(int), TCPdaytimed(int), TCPtimed(int);

#include "passiveTCP.c"
#include "passiveUDP.c"
//int  passiveTCP(const char *service, int qlen);
//int  passiveUDP(const char *service);
//int  errexit(const char *format, ...);


int UDPgtod(int sock);
int TCPgtod(int fd);

int UDPgtod(int sock) {
	char out_buf[8];
	struct timeval now;
        struct sockaddr fsin;
	int alen;
	char buf[1024];
		

		if (recvfrom(sock, buf, sizeof(buf), 0,
			(struct sockaddr *)&fsin, &alen) < 0)
			errexit("recvfrom: %s\n",
			strerror(errno));

		(void) gettimeofday(&now,NULL);
		printf("(UDP)%x %x\n",now.tv_sec,now.tv_usec);
		
		now.tv_sec = htonl(now.tv_sec);
		now.tv_usec = htonl(now.tv_usec);
		memcpy(&out_buf[0],&now.tv_sec,4);
		memcpy(&out_buf[4],&now.tv_usec,4);
		(void) sendto(sock, &out_buf, sizeof(out_buf),0,(struct sockaddr *)&fsin,sizeof(fsin));
		return 0; 
}



int TCPgtod(int fd) {
	char buf[8];
	struct timeval now;

	(void) gettimeofday(&now,NULL);
	printf("(TCP)%x %x\n",now.tv_sec,now.tv_usec);
	now.tv_sec = htonl(now.tv_sec);
	now.tv_usec = htonl(now.tv_usec);
	memcpy(&buf[0],&now.tv_sec,4);
	memcpy(&buf[4],&now.tv_usec,4);
	(void) write(fd, buf, 8);
        return 0;
}


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
void  doTCP(struct service *psv);
void  reaper(int sig);

/*
struct service svent[] =
  {  { "echo", TCP_SERV, NOSOCK, TCPechod },
    { "chargen", TCP_SERV, NOSOCK, TCPchargend },
    { "daytime", TCP_SERV, NOSOCK, TCPdaytimed },
    { "time", TCP_SERV, NOSOCK, TCPtimed },
    { 0, 0, 0, 0 },
  };
*/

struct service svent[] = 
	{	{"5001",UDP_SERV,NOSOCK,UDPgtod },
		{"5002",TCP_SERV,NOSOCK,TCPgtod },
		{"5003",TCP_SERV,NOSOCK,serv },
		{0,0,0,0}
	};

#ifndef  MAX
#define  MAX(x, y)  ((x) > (y) ? (x) : (y))
#endif  /* MAX */

#define  QLEN      5

#define  LINELEN    128

extern  u_short  portbase;  /* from passivesock()  */

/*------------------------------------------------------------------------
 * main - Super-server main program
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
  struct service  *psv,    /* service table pointer  */
    *fd2sv[NOFILE];    /* map fd to service pointer  */
  int  fd, nfds;
  fd_set  afds, rfds;    /* readable file descriptors  */

  switch (argc) {
  case 1:
    break;
  case 2:
    portbase = (u_short) atoi(argv[1]);
    break;
  default:
    errexit("usage: superd [portbase]\n");
  }

  nfds = 0;
  FD_ZERO(&afds);
  for (psv = &svent[0]; psv->sv_name; ++psv) {
    if (psv->sv_useTCP)
      psv->sv_sock = passiveTCP(psv->sv_name, QLEN);
    else
      psv->sv_sock = passiveUDP(psv->sv_name);
    fd2sv[psv->sv_sock] = psv;
    nfds = MAX(psv->sv_sock+1, nfds);
    FD_SET(psv->sv_sock, &afds);
  }
  (void) signal(SIGCHLD, reaper);

  while (1) {
    memcpy(&rfds, &afds, sizeof(rfds));
    if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
        (struct timeval *)0) < 0) {
      if (errno == EINTR)
        continue;
      errexit("select error: %s\n", strerror(errno));
    }
    for (fd=0; fd<nfds; ++fd)
      if (FD_ISSET(fd, &rfds)) {
        psv = fd2sv[fd];
        if (psv->sv_useTCP)
          	doTCP(psv);
        else
      		psv->sv_func(psv->sv_sock);
      }
  }
}

void
doTCP(struct service *psv)
{
  struct sockaddr_in fsin;  /* the request from address  */
  int  alen;      /* from-address length    */
  int  fd, ssock;

  alen = sizeof(fsin);
  ssock = accept(psv->sv_sock, (struct sockaddr *)&fsin, &alen);
  if (ssock < 0)
    errexit("accept: %s\n", strerror(errno));
  switch (fork()) {
  case 0:  
    break;
  case -1:
    errexit("fork: %s\n", strerror(errno));
  default:
    (void) close(ssock);
    return;    /* parent */
  }
  /* child */

  /* Leave stdout and stderr open for printing error messages */
  for (fd = NOFILE; fd >= 3; --fd)
    if (fd != ssock)
      (void) close(fd);
  exit(psv->sv_func(ssock));
}

/*------------------------------------------------------------------------
 * reaper - clean up zombie children
 *------------------------------------------------------------------------
 */
void
reaper(int sig)
{
  int  status;

  while (wait3(&status, WNOHANG, (struct rusage *)0) > 0)
    /* empty */;
  /* changed from >= to > because it hung waiting for all
     children to exit  -- 11 Sept 96  djv */
}
