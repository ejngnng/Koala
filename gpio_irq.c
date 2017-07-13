#include <stdio.h>
#include <poll.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define GPIO_FN_MAXLEN	32
#define POLL_TIMEOUT	0
#define RDBUF_LEN	5

int main(int argc, char **argv) {
	char fn[GPIO_FN_MAXLEN];
	int fd,ret;
	struct pollfd pfd;
	char rdbuf[RDBUF_LEN];
    char *gpio = "25"; // interrupt BCM gpio 25

	memset(rdbuf, 0x00, RDBUF_LEN);
	memset(fn, 0x00, GPIO_FN_MAXLEN);

	snprintf(fn, GPIO_FN_MAXLEN-1, "/sys/class/gpio/gpio%s/value", gpio);

	fd=open(fn, O_RDONLY);
	if(fd<0) {
		perror(fn);
		return 2;
	}
	pfd.fd=fd;
	pfd.events=POLLPRI;
	
	ret=read(fd, rdbuf, RDBUF_LEN-1);
	if(ret<0) {
		perror("read()");
		return 4;
	}
//	printf("value is: %s\n", rdbuf);
	
	while(1) {
		memset(rdbuf, 0x00, RDBUF_LEN);
		lseek(fd, 0, SEEK_SET);
		ret=poll(&pfd, 1, POLL_TIMEOUT);
		if(ret<0) {
			perror("poll()");
			close(fd);
			return 3;
		}
		if(ret==0) {
//			printf("timeout\n");
			continue;
		}
		ret=read(fd, rdbuf, RDBUF_LEN-1);
		if(ret<0) {
			perror("read()");
			return 4;
		}
		printf("interrupt, value is: %s\n", rdbuf);
	}
	close(fd);
	return 0;
}
