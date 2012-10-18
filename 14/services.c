#include <sys/time.h>
#include <string.h>
#include <stdio.h>

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
